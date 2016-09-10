#include "Leaderboard.h"
#include <string>
//#include <fstream>
//use a graph for player friends

void leaderboard::ReadFile(){
	std::string filename = "test.txt";
	std::string function;
	std::string arguments;

	std::cout<<"Please enter the filename you wish to import from"<<std::endl;
	std::cin>>filename;
	
	std::ifstream ifs(filename);
	while(ifs){
		ifs >> function >> arguments; //TODO: might 
		Parse(function, arguments);	//determines function and parses arguments
	}
}
void leaderboard::ReadConsole(){
	std::string function;
	std::string arguments;
	
	std::cout<<"Continue entering commands with enter between each full command, enter 'q' to quit."<<std::endl;
	std::getline(std::cin, arguments); //trash first line
	while (arguments != "q"){
		std::getline(std::cin, arguments);
		if (arguments != "q"){
			std::string function = arguments.substr(0, arguments.find(" "));
		    arguments = arguments.substr(arguments.find(" ")+1, arguments.length()-function.length());
			
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
	
}
void leaderboard::AddVictory(int game_id, int vict_id, std::string vict_name, int vict_points){
	
}
void leaderboard::Plays(int player_id, int game_id, std::string player_ign){
	
}
void leaderboard::AddFriends(int player_id1, int player_id2){
	
}
void leaderboard::WinVictory(int player_id, int game_id, int vict_id){
	
}
void leaderboard::FriendsWhoPlay(int player_id, int game_id){

}
void leaderboard::ComparePlayers(int player_id1, int player_id2){
	
}
void leaderboard::SummarizePlayer(int player_id){
	
}
void leaderboard::SummarizeGame(int game_id){
	
}
void leaderboard::SummarizeVictory(int game_id, int vict_id){
	
}
void leaderboard::VictoryRanking(){
	
}

//Constructors
leaderboard::player::player(int player_id, std::string player_name){	//Might need leaderboard::
	points = 0;
	id = player_id;
	name = player_name;
}
leaderboard::game::game(int game_id, std::string game_name){	//Might need leaderboard::
	id = game_id;
	name = game_name;
}
leaderboard::victory::victory(int game_id_num, int vict_id, std::string vict_name, int vict_points){
	id = vict_id;
	game_id = game_id_num;
	name = vict_name;
	points = vict_points;
}
void leaderboard::Parse(std::string function, std::string arguments){	//determines function and parses arguments
	
	if (function == "AddPlayer"){
		int position = arguments.find("\"");
		std::string id = arguments.substr(0,position-1);	//Get player_id
		std::string name = arguments.substr(position+1, arguments.length()-2-position);	//Get player_name
		AddPlayer(std::stoi(id), name);
	}
	else if (function == "AddGame"){
		int position = arguments.find("\"");
		std::string id = arguments.substr(0,position-1);	//Get game_id
		std::string name = arguments.substr(position+1, arguments.length()-2-position);	//Get game_name
		AddGame(std::stoi(id), name);
	}
	else if (function == "AddVictory"){
		int position = arguments.find(" ");
		std::string game_id = arguments.substr(0,position);	//Get game_id
		//std::cout<<"game id = "<<game_id<<std::endl;
		arguments = arguments.substr(position+1, arguments.length()-1-game_id.length());	//TODO: might need to be -1		position = arguments.find(" ");
		std::string vict_id = arguments.substr(0,position);	//Get vict_id
		//std::cout<<"Vict id = "<<vict_id<<std::endl;
		arguments = arguments.substr(position+1, arguments.length()-1-game_id.length());
		position = arguments.find(" ");
		std::string vict_name = arguments.substr(1,position-2); //Get vict_name
		//std::cout<<"vict name = "<<vict_name<<std::endl;
		std::string vict_points = arguments.substr(position+1, arguments.length()-1-vict_name.length());	//Get vict_points
		//std::cout<<"Vict points = " <<vict_points<<std::endl;

		AddVictory(std::stoi(game_id), std::stoi(vict_id), vict_name, std::stoi(vict_points));
	}
	else if (function == "Plays"){
		int position = arguments.find(" ");
		std::string player_id = arguments.substr(0,position);	//Get player_id
		//std::cout<<"Player id = "<<player_id<<std::endl;
		arguments = arguments.substr(position+1, arguments.length()-1-player_id.length());	//TODO: might need to be -1		position = arguments.find(" ");
		std::string game_id = arguments.substr(0,position);	//Get game_id
		//std::cout<<"game_ id = "<<game_id<<std::endl;
		arguments = arguments.substr(position+1, arguments.length()-1-game_id.length());
		std::string player_ign = arguments.substr(position, arguments.length()-1-game_id.length()); //Get player_ign
		//std::cout<<"player name = "<<player_ign<<std::endl;

		Plays(std::stoi(player_id), std::stoi(game_id), player_ign);
	}
	else if (function == "AddFriends"){
		int position = arguments.find(" ");
		std::string player_id1 = arguments.substr(0,position);	//Get player_id1
		std::string player_id2 = arguments.substr(position+1, arguments.length()-1-player_id1.length()); //Get player_ign
		//std::cout<< "1 = "<< player_id1 << "2 = " << player_id2<<std::endl;
		
		AddFriends(std::stoi(player_id1), std::stoi(player_id2));
	}
	else if (function == "WinVictory"){
		int position = arguments.find(" ");
		std::string player_id = arguments.substr(0,position);	//Get player_id
		//std::cout<<"Player id = "<<player_id<<std::endl;
		arguments = arguments.substr(position+1, arguments.length()-1-player_id.length());	//TODO: might need to be -1		position = arguments.find(" ");
		std::string game_id = arguments.substr(0,position);	//Get game_id
		//std::cout<<"Game_ id = "<<game_id<<std::endl;
		std::string vict_id = arguments.substr(position+1, arguments.length()-1-game_id.length()); //Get vict_id
		//std::cout<<"Vict id = "<<vict_id<<std::endl;

		WinVictory(std::stoi(player_id), std::stoi(game_id), std::stoi(vict_id));
	}
	else if (function == "FriendsWhoPlay"){
		
	}
	else if (function == "ComparePlayers"){
		
	}
	else if (function == "SummarizePlayer"){
		
	}
	else if (function == "SummarizeGame"){
		
	}
	else if (function == "SummarizeVictory"){
		
	}
	else if (function == "VictoryRanking"){
		
	}
	else if (function == ""){
		std::cout<<"Empty line"<<std::endl;
	}
	else{
		std::cout<<"No matching function"<<std::endl;
	}
}
