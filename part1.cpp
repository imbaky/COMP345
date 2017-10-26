#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <fstream>
#include <dirent.h>
#include <vector>

#include "./utils.h"
#include "./lib/player.h"
#include "./lib/card.h"

#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

using namespace std;

int main()
{
	cout << "██████╗ ██╗███████╗██╗  ██╗\n"<<
		"██╔══██╗██║██╔════╝██║ ██╔╝\n"<<
		"██████╔╝██║███████╗█████╔╝ \n"<<
		"██╔══██╗██║╚════██║██╔═██╗ \n"<<
		"██║  ██║██║███████║██║  ██╗\n"<<
		"╚═╝  ╚═╝╚═╝╚══════╝╚═╝  ╚═╝\n\n" << endl;
	start_game();
    
	Map *map = loadMap();
	/* TODO check if map is valid 
	 * Need to implement isValid()
	 */ 

	int countriesCount = 0;
	vector<Continent *> continents = map->getContinents();
	for (int i = 0; i < continents.size(); i++) {
		countriesCount += continents[i]->getCountries().size();
	}

	Deck *deck = createDeck(countriesCount);
    
	vector<Player *> players = createPlayers();

	cout << "\n\n===\nMAP:\n===\n";
	for (int i = 0; i < continents.size(); i++) {
		cout << "CONTINENT: " << continents[i]->name << "\n------------------------\n";
		vector<Country *> countries = continents[i]->getCountries();
		for (int j = 0; j < countries.size(); j++) {
			cout << countries[j]->name << ": ";
			vector<Country *> neighbors = countries[j]->getNeighbors();
			for (int k = 0; k < neighbors.size(); k++) {
				cout << neighbors[k]->name << ", ";
			}
			cout << "\n";
		}
		cout << "\n";
        }

	cout << "\n\n=======\nPLAYERS:\n=======\n";
	for (int i = 0; i < players.size(); i++) {
		cout << players[i]->name << ": " << players[i]->getDice()->getDices().size() << " dices\n";
	}

	cout << "\n\n====\nDECK:\n====\nCreated " << countriesCount - (countriesCount % 3) << " card deck\n";
	
	return 0;
}
