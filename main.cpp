//TODO: #include things
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Leaderboard.cpp"

using namespace std;	//or no namespace
int main(){
	leaderboard my_leaderboard;
	my_leaderboard.ReadConsole();
	/*
	string answer = "";
	while (answer != "1" && answer != "2" && answer != "q"){
		
		cout<< "Enter (1) if the input is a text file or (2) if the input is through the console or (q) to quit."<<endl;
		cin>>answer;
		if (answer == "1"){
			my_leaderboard.ReadFile();
		}
		else if (answer == "2"){
			my_leaderboard.ReadConsole();
		}
		else if (answer == "q"){
			cout << "Exiting" << endl;
		}
		else{
			cout<<"Please enter either a 1 or a 2"<<endl;
		}
	}*/
}