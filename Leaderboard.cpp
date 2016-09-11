#include "Leaderboard.h"
#include <string>
#include <algorithm>
#include <iomanip>


void leaderboard::ReadConsole(){
	std::string function;
	std::string arguments;
	
	std::cout<<"Continue entering commands with enter between each full command, enter 'q' to quit."<<std::endl;
	while (std::getline(std::cin, arguments) && arguments != "q"){
		if (arguments != "q"){
			std::string function = arguments.substr(0, arguments.find(" "));
		    arguments = arguments.substr(arguments.find(" ")+1, arguments.length()-function.length());	//Separate function & arguments
			
		    Parse(function, arguments);
		}
		else{
			std::cout<<"Quit"<<std::endl;
		}
	}
}
void leaderboard::AddPlayer(int player_id, std::string player_name){
	player new_player(player_id, player_name);
	player_map.insert(std::pair<int,player>(player_id, new_player));
}
void leaderboard::AddGame(int game_id, std::string game_name){
	game new_game(game_id, game_name);
	game_map.insert(std::pair<int,game>(game_id, new_game));
}
void leaderboard::AddVictory(int game_id, int vict_id, std::string vict_name, int vict_points){
	victory new_victory(game_id, vict_id, vict_name, vict_points);
	victory_map.insert(std::pair<int,victory>(vict_id, new_victory));
	auto vict_it = victory_map.find(vict_id);
	auto game_it = game_map.find(game_id);
	game_it->second.victories.insert(std::pair<int,victory*>(vict_id, &(vict_it->second)));	//Add victories to game
}
void leaderboard::Plays(int player_id, int game_id, std::string player_ign){	
	ign new_ign(player_ign);
	auto game_it = game_map.find(game_id);
	auto player_it = player_map.find(player_id);
	game* game_pointer = &(game_it->second);
	player* player_pointer = &(player_it->second);
	player_it->second.games.insert(std::pair<int,game*>(game_id, game_pointer));	//Add game to player
	game_it->second.players.insert(std::pair<int,player*>(player_id,player_pointer));	//Add player to game
	game_it->second.stats.insert(std::pair<int, ign>(player_id, new_ign));
}
void leaderboard::AddFriends(int player_id1, int player_id2){
	auto player1_it = player_map.find(player_id1);
	auto player2_it = player_map.find(player_id2);
	player* player1_pointer = &(player1_it->second);
	player* player2_pointer = &(player2_it->second);
	player1_it->second.friends.insert(std::pair<int,player*>(player_id2,player2_pointer));	//Add player2 as friend
	player2_it->second.friends.insert(std::pair<int,player*>(player_id1,player1_pointer));	//Add player1 as friend
}
void leaderboard::WinVictory(int player_id, int game_id, int vict_id){
	auto player_it = player_map.find(player_id);
	auto game_it = game_map.find(game_id);
	auto vict_it = victory_map.find(vict_id);
	victory* vict_pointer = &(vict_it->second);
	player* player_pointer = &(player_it->second);
	player_it->second.points += vict_it->second.points;	//Add points to player's total
	player_it->second.victories.insert(std::pair<int,victory*>(vict_id, vict_pointer));	//Add victory to player
	vict_it->second.players.insert(std::pair<int,player*>(player_id, player_pointer));	//Add player to victory
	auto stats_it = game_it->second.stats.find(player_id);
	stats_it->second.points += vict_it->second.points;	//Add points to player for this game
	stats_it->second.victories += 1;
	vict_it->second.victories += 1;
}
void leaderboard::FriendsWhoPlay(int player_id, int game_id){	
	auto player_it = player_map.find(player_id);
	for (auto friend_it = player_it->second.friends.begin(); friend_it != player_it->second.friends.end(); ++friend_it){
		auto found = friend_it->second->games.find(game_id);	//Search friends' games
		if (found != friend_it->second->games.end()){
			std::cout<<"Friend that has game "<<friend_it->second->name<<std::endl;	//Friend who plays found
		}
	}
}
void leaderboard::ComparePlayers(int player_id1, int player_id2, int game_id){	
	auto player_it1 = player_map.find(player_id1);
	auto player_it2 = player_map.find(player_id2);
	auto game_it = game_map.find(game_id);
	auto stats_it1 = game_it->second.stats.find(player_id1);
	auto stats_it2 = game_it->second.stats.find(player_id2);
	int length = player_it1->second.name.length();
	//Text formatting
	std::cout<<'\n'<<player_it1->second.name<<" vs "<<player_it2->second.name<<" in "<<game_it->second.name<<std::endl;	
	std::cout <<"  Player\t    Victories\t Victory Points\t IGN"<<std::endl;
	std::cout<<"_________________________________________________________________________________"<<std::endl;
	std::cout<<std::internal<<std::setw(1)<<1<<". "<<player_it1->second.name<<" "<<std::setw(20-length);	//Print player1
	std::cout<<stats_it1->second.victories<<"/";	
	std::cout<<game_it->second.victories.size()<<std::setw(8)<<" "<<stats_it1->second.points<<" pts";
	length = (std::to_string(stats_it1->second.points).length());	//length of argument so text lines up
	std::cout<<std::left<<std::setw(10-length)<<" "<<stats_it1->second.username<<std::endl;
	length = player_it2->second.name.length();
	std::cout<<std::internal<<std::setw(1)<<2<<". "<<player_it2->second.name<<" "<<std::setw(20-length)<<stats_it2->second.victories<<"/";	//Print player2
	std::cout<<game_it->second.victories.size()<<std::setw(8)<<" "<<stats_it2->second.points<<" pts";
	length = (std::to_string(stats_it2->second.points).length());
	std::cout<<std::left<<std::setw(10-length)<<" "<<stats_it2->second.username<<'\n'<<std::endl;
}
void leaderboard::SummarizePlayer(int player_id){	
	auto player_it = player_map.find(player_id);
	std::cout<<"\nPlayer name: "<<player_it->second.name<<"\nTotal Victory Points: "<<player_it->second.points<<" pts\n"<<std::endl; //Print player
	std::cout <<"  Game\t\t  Victories\tVictory Points\tIGN"<<std::endl;
	std::cout<<"_________________________________________________________________________"<<std::endl;
	int i = 1;
	for (auto game_it = player_it->second.games.begin(); game_it != player_it->second.games.end(); ++game_it){	//Print games & victories
		auto stats_it = game_it->second->stats.find(player_id);
		int length = game_it->second->name.length();
		//Text formatting
		std::cout<<std::internal<<std::setw(1)<<i<<". "<<game_it->second->name<<" "<<std::setw(20-length)<<stats_it->second.victories<<"/";
		std::cout<<game_it->second->victories.size()<<std::setw(8)<<" "<<stats_it->second.points<<" pts";
		length = (std::to_string(stats_it->second.points).length());
		std::cout<<std::left<<std::setw(10-length)<<" "<<stats_it->second.username<<std::endl;
		i +=1;
	}
	std::cout<<"\n  Friend\t   Victory Points"<<std::endl;
	std::cout<<"____________________________________________"<<std::endl;
	i = 1;
	for (auto friend_it = player_it->second.friends.begin(); friend_it != player_it->second.friends.end(); ++friend_it){	//Print friends
		std::cout<<std::setw(1)<<std::left <<i<<". "<<friend_it->second->name<<std::setw(23-friend_it->second->name.length())<<" ";
		std::cout<<friend_it->second->points<<std::endl;
		i +=1;
	}
	std::cout<<'\n';	
}
void leaderboard::SummarizeGame(int game_id){	
	auto game_it = game_map.find(game_id);
	std::cout<<"Game name: "<<game_it->second.name<<std::endl;	//Print game
	std::cout <<"  Player\t      Victories\t Victory Points\t    IGN"<<std::endl;
	std::cout<<"_____________________________________________________________________________"<<std::endl;
	int i = 1;
	for (auto player_it = game_it->second.players.begin(); player_it!= game_it->second.players.end(); ++player_it){	//Print players
		auto stats_it = game_it->second.stats.find(player_it->first);
		int length = player_it->second->name.length();
		//Text formatting
		std::cout<<std::internal<<std::setw(1)<<i<<". "<<player_it->second->name<<" "<<std::setw(23-length)<<stats_it->second.victories<<"/";		
		std::cout<<game_it->second.victories.size()<<std::setw(8)<<" "<<stats_it->second.points<<" pts";
		length = (std::to_string(stats_it->second.points).length());
		std::cout<<std::left<<std::setw(10-length)<<" "<<stats_it->second.username<<std::endl;
		i +=1;
	}
	i = 1;
	std::cout <<"\n  Victory\t     Players Completed"<<std::endl;
	std::cout<<"___________________________________________________________"<<std::endl;
	for (auto vict_it = game_it->second.victories.begin(); vict_it != game_it->second.victories.end(); ++vict_it){
		int length = vict_it->second->name.length();
		std::cout<<std::setw(1)<<std::left <<i<<". "<<vict_it->second->name<<std::setw(23-length)<<" ";
		std::cout<<vict_it->second->victories<<std::endl;
		i +=1;
	}
	std::cout<<'\n';
	
}
void leaderboard::SummarizeVictory(int game_id, int vict_id){	//TODO: percentage of players who play that game who have the Victory.
	auto vict_it = victory_map.find(vict_id);
	auto game_it = game_map.find(game_id);
	//Text formatting
	std::cout<<"\nVictory name: "<<vict_it->second.name<<"\nGame: "<<game_it->second.name<<" for ";	//Print victory & game names
	std::cout<<vict_it->second.points<<" pts"<<std::endl;	
	int i = 1;
	std::cout<<"______________________________________"<<std::endl;
	for (auto player_it = vict_it->second.players.begin(); player_it!= vict_it->second.players.end(); ++player_it){ //Print players
		std::cout<<i<<". "<<player_it->second->name<<std::endl;
		i += 1;
	}
	int percentage = (100*vict_it->second.players.size())/(game_it->second.players.size());
	std::cout<<"\n (*) "<<percentage<<"% of players have completed this victory"<<std::endl;
	std::cout<<'\n';
}
void leaderboard::VictoryRanking(){
	std::map<int, player*> ranking;
	for (auto player_it = player_map.begin(); player_it!= player_map.end(); ++player_it){	//Reorder players by points
		ranking.insert(std::pair<int,player*>(player_it->second.points, &(player_it->second)));
	}
	int i = 1;
	std::cout<<"Global Victory Ranking:\n Player \t\t Points"<<std::endl;
	std::cout<<"______________________________________"<<std::endl;
	for (auto player_it = ranking.rbegin(); player_it!= ranking.rend(); ++player_it){	//Print players in order
		std::cout <<std::setw(1)<<std::left <<i<<". "<<player_it->second->name<<std::setw(23-player_it->second->name.length())<<" "<<player_it->second->points<<std::endl;
		i++;
	}
}

//Parse logic
void leaderboard::Parse(std::string function, std::string arguments){	//determines function and parses arguments
	
	if (function == "AddPlayer"){
		int position = arguments.find("\"");
		std::string player_id = arguments.substr(0,position-1);	//Get player_id
		std::string player_name = arguments.substr(position+1, arguments.length()-2-position);	//Get player_name

		AddPlayer(std::stoi(player_id), player_name);
	}
	else if (function == "AddGame"){
		int position = arguments.find("\"");
		std::string game_id = arguments.substr(0,position-1);	//Get game_id
		std::string game_name = arguments.substr(position+1, arguments.length()-2-position);	//Get game_name

		AddGame(std::stoi(game_id), game_name);
	}
	else if (function == "AddVictory"){
		int position = arguments.find(" ");
		std::string game_id = arguments.substr(0,position);	//Get game_id
		arguments = arguments.substr(position+1, arguments.length()-1-game_id.length());
		std::string vict_id = arguments.substr(0,position);	//Get vict_id
		position = arguments.find(" ");
		arguments = arguments.substr(position+2, arguments.length()-1-game_id.length());
		position = arguments.find("\"");
		std::string vict_name = arguments.substr(0,position); //Get vict_name
		std::string vict_points = arguments.substr(vict_name.length()+1, arguments.length()-1-vict_name.length());	//Get vict_points

		AddVictory(std::stoi(game_id), std::stoi(vict_id), vict_name, std::stoi(vict_points));
	}
	else if (function == "Plays"){
		int position = arguments.find(" ");
		std::string player_id = arguments.substr(0,position);	//Get player_id
		position = arguments.find(" ");
		arguments = arguments.substr(position+1, arguments.length()-1-player_id.length());
		std::string game_id = arguments.substr(0,position);	//Get game_id
		position = arguments.find(" ");
		std::string player_ign = arguments.substr(position+2, arguments.length()-2-game_id.length());	//Get player_ign

		Plays(std::stoi(player_id), std::stoi(game_id), player_ign);
	}
	else if (function == "AddFriends"){
		int position = arguments.find(" ");
		std::string player_id1 = arguments.substr(0,position);	//Get player_id1
		std::string player_id2 = arguments.substr(position+1, arguments.length()-1-player_id1.length()); //Get player_id2
		
		AddFriends(std::stoi(player_id1), std::stoi(player_id2));
	}
	else if (function == "WinVictory"){
		int position = arguments.find(" ");
		std::string player_id = arguments.substr(0,position);	//Get player_id
		arguments = arguments.substr(position+1, arguments.length()-1-player_id.length());
		position = arguments.find(" ");
		std::string game_id = arguments.substr(0,position);	//Get game_id
		std::string vict_id = arguments.substr(position+1, arguments.length()-1-game_id.length()); //Get vict_id

		WinVictory(std::stoi(player_id), std::stoi(game_id), std::stoi(vict_id));
	}
	else if (function == "FriendsWhoPlay"){	
		int position = arguments.find(" ");
		std::string player_id = arguments.substr(0,position);	//Get player_id
		std::string game_id = arguments.substr(position+1, arguments.length()-1-player_id.length()); //Get game_id

		FriendsWhoPlay(std::stoi(player_id), std::stoi(game_id));
	}
	else if (function == "ComparePlayers"){
		int position = arguments.find(" ");
		std::string player_id1 = arguments.substr(0,position);	//Get player_id1
		arguments = arguments.substr(position+1, arguments.length()-1-player_id1.length());
		position = arguments.find(" ");
		std::string player_id2 = arguments.substr(0, position); //Get player_id2
		std::string game_id = arguments.substr(position+1, arguments.length()-1-player_id2.length());

		ComparePlayers(std::stoi(player_id1), std::stoi(player_id2), std::stoi(game_id));
	}
	else if (function == "SummarizePlayer"){
		std::string player_id = arguments;	//Get player_id
		SummarizePlayer(std::stoi(player_id));
	}
	else if (function == "SummarizeGame"){
		std::string game_id = arguments;	//Get game_id
		SummarizeGame(std::stoi(game_id));
	}
	else if (function == "SummarizeVictory"){
		int position = arguments.find(" ");
		std::string game_id = arguments.substr(0,position);	//Get game_id
		std::string vict_id = arguments.substr(position+1, arguments.length()-1-game_id.length()); //Get vict_id

		SummarizeVictory(std::stoi(game_id), std::stoi(vict_id));
	}
	else if (function == "VictoryRanking"){
		VictoryRanking();
	}
	else if (function == ""){
		//std::cout<<"Empty line"<<std::endl;
	}
	else{
		std::cout<<"No matching function"<<std::endl;
	}
}

//Constructors
leaderboard::ign::ign(std::string name){
	username = name;
	victories = 0;
	points = 0;
}
leaderboard::player::player(int player_id, std::string player_name){	
	points = 0;
	id = player_id;
	name = player_name;
}
leaderboard::game::game(int game_id, std::string game_name){	
	id = game_id;
	name = game_name;
}
leaderboard::victory::victory(int game_id_num, int vict_id, std::string vict_name, int vict_points){
	id = vict_id;
	game_id = game_id_num;
	name = vict_name;
	points = vict_points;
	victories = 0;
}