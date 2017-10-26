#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <fstream>
#include <dirent.h>
#include <vector>

#include "./utils.h"
#include "./lib/Maploader.h"
#include "./lib/player.h"
#include "./lib/card.h"

#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

using namespace std;

// function declaration
void start_game();
string select_map();
int players_number();


Map *loadMap() {
	MapLoader *ml = new MapLoader();
	ml->loadMap(select_map());
	Map *map = ml->getMap();
	return map;
}

Deck *createDeck(int countries) {
	Deck* deck = new Deck(countries);
	return deck;
}

vector<Player *> createPlayers() {
	int playerCount = players_number();
	vector<Player *> players;
	for (int i = 0; i < playerCount; i++) {
		Player *newPlayer = new Player("Player "+to_string(i + 1), 3);
		players.push_back(newPlayer);
	}
	return players;
}

void start_game(){
	bool valid_input=false;
	char input;
	while(!valid_input){
		cout<<"Would you like to start the game? (y/n)"<<endl;
		cin>>input;
		if(input=='y'){
			valid_input=true;
		}else if(input!='n')
			cerr<<"invalid input !!"<<endl;
	}
}


string select_map(){
	bool valid_input = false;
	int input;

	DIR *pDIR;
	struct dirent *entry;
	int count = 0;
	vector<string> files;
    
	cout << "\n\n***Available maps***" << endl;
	if (pDIR = opendir("./maps/") ){
		while(entry = readdir(pDIR)) {
			if(strcmp(entry->d_name, ".") != 0 &&
			   strcmp(entry->d_name, "..") != 0 &&
			   entry->d_name[strlen(entry->d_name)-2] == 'a') {
				files.push_back(entry->d_name);
				cout << ++count << "- " << entry->d_name << "\n";
			}
		}
		closedir(pDIR);
	}
	while (!valid_input){
		cout << "Which map would you like to use? (enter number)" << endl;
		cin >> input;
		if ((input >= 1) && (input <= count)){
			valid_input = true;
		} else
			cerr << "invalid input !!"<<endl;
               
	}
	return "./maps/" + files.at(input - 1);
}

int players_number(){
	bool valid_input=false;
	int input;
	while(!valid_input){
		cout<<"Select the number of players in the game (2-6 players)"<<endl;
		cin>>input;
		if((input>=2)&&(input<=6)){
			valid_input=true;
		}else 
			cerr<<"invalid input !!"<<endl;
	}
	return input;
}

void reinforcementPhase(Player *player) {
	int owned = player->getCountries().size();
	int additionalArmies = owned / 3;
	if (additionalArmies < 3)
		additionalArmies = 3;
	player->setArmies(player->getArmies() + additionalArmies);
	
}
