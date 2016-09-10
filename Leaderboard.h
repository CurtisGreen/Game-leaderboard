#ifndef Leaderboard_h
#define Leaderboard_h

#include <map>


class leaderboard{
	
	//Data Structures
	struct game;
	struct victory;
	struct ign{				//Stores data relating to specific game
		ign(std::string name);
		std::string username;	
		int victories;
		int points;			//Points per game
	};
	struct player{
		player(int player_id, std::string player_name);
		int id;
		std::string name;
		int points;
		std::map<int, game*> games;	
		std::map<int, victory*> victories;
		std::map<int, player*> friends;
	};
	struct game{
		game(int game_id, std::string game_name);
		int id;
		std::string name;
		std::map<int, ign> stats;
		std::map<int, victory*> victories;
		std::map<int, player*> players;
	};
	struct victory{
		victory(int game_id, int vict_id, std::string vict_name, int vict_points);
		int id;
		int game_id;
		std::string name;
		int points;
		std::map<int,player*> players;
	};
	
	//Data
	std::map<int, player> player_map;
	std::map<int, game> game_map;
	std::map<int, victory> victory_map;
	
	public:
	
	//void ReadFile();
	void ReadConsole();
	
	//Leaderboard actions
	void AddPlayer(int player_id, std::string player_name);
	void AddGame(int game_id, std::string game_name);
	void AddVictory(int game_id, int vict_id, std::string vict_name, int vict_points);
	void Plays(int player_id, int game_id, std::string player_ign);
	void AddFriends(int player_id1, int player_id2);
	void WinVictory(int player_id, int game_id, int vict_id);
	void FriendsWhoPlay(int player_id, int game_id);
	void ComparePlayers(int player_id1, int player_id2);
	void SummarizePlayer(int player_id);
	void SummarizeGame(int game_id);
	void SummarizeVictory(int game_id, int vict_id);
	void VictoryRanking();
	
	void Parse(std::string function, std::string arguments);
	
	
};
#endif


