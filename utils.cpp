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


Map *loadMap()
{
	MapLoader *ml = new MapLoader();
	ml->loadMap(select_map());
	Map *map = ml->getMap();
	return map;
}

Deck *createDeck(int countries)
{
	Deck* deck = new Deck(countries);
	return deck;
}

vector<Player *> createPlayers()
{
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


string select_map()
{
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

int players_number()
{
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

void reinforcementPhase(Player *player, Map *map)
{
	char input;
	bool validInput = false;
	int owned = player->getCountries().size();
	int additionalArmies = owned / 3;
	if (additionalArmies < 3)
		additionalArmies = 3;
	additionalArmies += numOfContinents(player, map);

	while (!validInput) {
		cout << "Exchange cards? (y/n)\n";
		cin >> input;
		if (input == 'y') {
			cout << "(0) Echange infantries\n";
			cout << "(1) Echange cavaleries\n";
			cout << "(2) Echange artilleries\n";
			cout << "(3) Echange all\n";
			cin >> input;
			switch (input) {
			case '0':
				additionalArmies = player->getHand()->exchange(Infantry);
				player->setArmies(player->getArmies() + additionalArmies);
				validInput = true;

				break;
			case '1':
				additionalArmies = player->getHand()->exchange(Cavalery);
				player->setArmies(player->getArmies() + additionalArmies);
				validInput = true;

				break;
			case '2':
				additionalArmies = player->getHand()->exchange(Artillery);
				player->setArmies(player->getArmies() + additionalArmies);
				validInput = true;

				break;
			case '3':
				additionalArmies = player->getHand()->exchange();
				player->setArmies(player->getArmies() + additionalArmies);
				validInput = true;
				break;
			default:
				cout << "Invalid input\n";
				validInput = false;
				break;
			}
		}
		if (input == 'n')
			validInput = true;
	}
	player->setArmies(player->getArmies() + additionalArmies);
}

void attackPhase(Player *player ,Map *mp)
{
	char input;
	bool validInput = false;
	while(!validInput) {
		cout << "Attack? (y/n)\n";
		cin >> input;
		if (input == 'y') {
			// Hash of the countries and neightbors it can attack
			map<string, vector<Country *>> validCountries;
			// A player's countries
			vector<Country *> countries = player->getCountries();
		
			for (int i = 0; i < countries.size(); i++) {
				if (countries[i]->getArmySize() < 2)
					continue;
				vector<Country *> enemyNeighbors;
				vector<Country *> neighbors = countries[i]->getNeighbors();
			
				for (int j = 0; j < neighbors.size(); j++) {
					if (!player->hasCountry(neighbors[i]->name)) {
						enemyNeighbors.push_back(neighbors[i]);
					}
				}
			
				if (enemyNeighbors.size() > 0)
					validCountries[countries[i]->name] = enemyNeighbors;
			}

			// Attacking country
			string attackFrom;
			cout << "Select country to attack from:\n";
			map<string, vector<Country *>>::iterator it;
			for (it = validCountries.begin(); it != validCountries.end(); it++) {
				cout << it->first << ", ";
			}
			cin >> attackFrom;
			if (validCountries.find(attackFrom) == validCountries.end()) {
				cout << "invalid country\n";
				continue;
			}

			// Attack target
			string attackTo;
			vector<Country *> targetNeighbors = validCountries[attackTo];
			cout << "Select country to attack:\n";
			for (int i = 0; i < validCountries[attackFrom].size(); i++) {
				cout << validCountries[attackFrom][i]->name << ", ";
			}
			cin >> attackTo;
			for (int i = 0; i < validCountries[attackTo].size(); i++) {
				if (targetNeighbors[i]->name == attackTo)
					validInput = true;
				break;
			}
		}
		if (input == 'n')
			validInput = true;
	}
}

void attack(Player *attacker, Player *defender, Country *c1, Country *c2)
{
	bool validInput = false;
	int attackerDices, defenderDices;
	int maxAttackerDices = c1->getArmySize(), maxDefenderDices = c2->getArmySize();
	
	while(!validInput) {
		cout << attacker->name << "Number of dices to attack (1, 2 or 3)?" << endl;
		cin >> attackerDices;
		if (attackerDices > '0' && attackerDices < '4' && attackerDices <= maxAttackerDices) {
			cout << defender->name << ": Number of dices to defend (1 or 2)?" << endl;
			cin >> defenderDices;
			if ((defenderDices == '1' || defenderDices == '2') && defenderDices <= maxDefenderDices) {
				validInput = true;
				// TODO: ROLL DICES FOR EACH PLAYER
				// COMPARE THE ROLLS
			}
		}
	}
}

void fortificationPhase(Player *player)
{
	char input;
	bool validInput = false;
	while (!validInput) {
		cout << "Fortify? (y/n)\n";
		cin >> input;
		if (input == 'y') {
			// Hash of the countries and neightbors it can attack
			map<string, vector<Country *>> validCountries;
			// A player's countries
			vector<Country *> countries = player->getCountries();

			for (int i = 0; i < countries.size(); i++) {
				vector<Country *> ownNeighbors;
				vector<Country *> neighbors = countries[i]->getNeighbors();

				for (int j = 0; j < neighbors.size(); j++) {
					if (player->hasCountry(neighbors[i]->name) &&
					    neighbors[i]->getArmySize() < 2) {
						ownNeighbors.push_back(neighbors[i]);
					}
				}

				if (ownNeighbors.size() > 0)
					validCountries[countries[i]->name] = ownNeighbors;
			}

			// Input country to fortify
			string fortifiee;
			cout << "Select country to fortify:\n";
			map<string, vector<Country *>>::iterator it;
			for (it = validCountries.begin(); it != validCountries.end(); it++) {
				cout << it->first << ", ";
			}
			cin >> fortifiee;
			if (validCountries.find(fortifiee) == validCountries.end()) {
				cout << "invalid country\n";
				continue;
			}

			// Input transferring country
			string fortifier;
			Country *fortifierPtr;
			vector<Country *> fortifiers = validCountries[fortifier];
			cout << "Select country to fortify from:\n";
			for (int i = 0; i < validCountries[fortifiee].size(); i++) {
				cout << validCountries[fortifiee][i]->name << ", ";
			}
			cin >> fortifier;
			for (int i = 0; i < validCountries[fortifiee].size(); i++) {
				if (fortifiers[i]->name == fortifier) {
					fortifierPtr = validCountries[fortifiee][i];
					validInput = true;
					break;
				}
			}

			if (!validInput) {
				cout << "Invalid input\n";
				continue;
			}

			// Transfer
			int transferAmount;
			int maxTransfer = fortifierPtr->getArmySize() - 1;
			cout << "Enter amount to transfer from " << fortifier << " to " << fortifiee <<
				" (1" << " to " << maxTransfer << ")\n";
			cin >> transferAmount;
			if (transferAmount > 0 && transferAmount <= maxTransfer) {
				validInput = true;
				Country *fortifieePtr;
				for (int i = 0; i < countries.size(); i++) {
					if (countries[i]->name == fortifiee)
						fortifieePtr = countries[i];
				}
				fortifieePtr->setArmySize(fortifieePtr->getArmySize() + transferAmount);
				fortifierPtr->setArmySize(fortifierPtr->getArmySize() - transferAmount);
			}
		}
		if (input == 'n')
			validInput = true;
	}
}

int numOfContinents(Player *player, Map *map)
{
	int owned = 0;	
	vector<Continent *> continents = map->getContinents();
	vector<Country *> countries = player->getCountries();

	for (int i = 0; i < continents.size(); i++) {
	       	vector<Country *> continentCountries = continents[i]->getCountries();
		for (int j = 0; j < continentCountries.size(); j++) {
			vector<Country *>::iterator it = find(countries.begin(), countries.end(), continentCountries[j]);
			if (it == countries.end()) {
				break;
			}
			if (j == continentCountries.size() - 1) {
				owned++;
			}
		}
	}

	return owned;
}

void printPlayerInfo(Player *player) {
	cout << player->name << ": " << player->getDice()->getDices().size() << " dices, "
	     << player->getArmies() << " armies\n";
}
