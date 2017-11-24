
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <fstream>
#include <dirent.h>
#include <vector>

#include "tournament.h"
#include "Maploader.h"

static string select_map_();

void Tournament::start() {
	setup();
}

void Tournament::setup() {
	bool valid_input = false;
	int numberOfMaps, numberOfComputers, numberOfGames, numberOfTurns;
	vector<vector<Game *>> mapGames;

	while (!valid_input) {
		cout << "Select the number of maps (1-5 players)" << endl;
		cin >> numberOfMaps;
		if ((numberOfMaps >= 1) && (numberOfMaps <= 5))
		{
			valid_input = true;
		}
		else
		{
			cin.clear();
			cin.ignore(100, '\n');
			cerr << "invalid input !!" << endl;
		}
	}

	valid_input = false;
	while (!valid_input) {
		cout << "Select the number of computers (2-4 players)" << endl;
		cin >> numberOfComputers;
		if ((numberOfComputers >= 2) && (numberOfComputers <= 4))
		{
			valid_input = true;
		}
		else
		{
			cin.clear();
			cin.ignore(100, '\n');
			cerr << "invalid input !!" << endl;
		}
	}

	valid_input = false;
	while (!valid_input) {
		cout << "Select the number of games per map (1-5 players)" << endl;
		cin >> numberOfGames;
		if ((numberOfGames >= 1) && (numberOfGames <= 5))
		{
			valid_input = true;
		}
		else
		{
			cin.clear();
			cin.ignore(100, '\n');
			cerr << "invalid input !!" << endl;
		}
	}

	valid_input = false;
	while (!valid_input) {
		cout << "Select the number of turns per game (10-50 players)" << endl;
		cin >> numberOfTurns;
		if ((numberOfTurns >= 10) && (numberOfTurns <= 50))
		{
			valid_input = true;
		}
		else
		{
			cin.clear();
			cin.ignore(100, '\n');
			cerr << "invalid input !!" << endl;
		}
	}

	for (int i = 0; i < numberOfMaps; i++) {
		vector<Game *> games;
		string gameMap;

		MapLoader *ml = new MapLoader();
		ml->loadMap(select_map_());

		for (int j = 0; j < numberOfGames; j++) {
			Game *g = new Game();
			g->setMap(ml->getMap());


			int countriesCount = 0;
			vector<Continent *> continents = g->getMap()->getContinents();
			for (int k = 0; k < continents.size(); k++) {
				countriesCount += continents[k]->getCountries().size();
			}
	
			g->createDeck(countriesCount);
			g->createPlayers(numberOfComputers);

			//Distribute countries between players
			int num_player = g->get_players().size();
			int index = 0;
			for (int k = 0; k < continents.size(); k++) {
				vector<Country *> countries = continents[k]->getCountries();
				for (int l = 0; l < countries.size(); l++) {
				 	g->get_players().at(index)->addCountry(countries[l]);

					countries[l]->owner = (g->get_players().at(index));
					index = (index + 1) % num_player;
				}
			}

			int initial_army = 40 - ((num_player - 2) * 5);
			//Distribute a players armies among their countries
			for (int k = 0; k < g->get_players().size(); k++) {
				int army_available = initial_army;
				vector<Country *> countries = g->get_players()[k]->getCountries();

				while (army_available > 0)
					for (int l = 0; l < countries.size(); l++) {
						if (army_available-- > 0) {
							countries[l]->setArmySize((countries[l]->getArmySize()) + 1);
						}
						else
							break;
					}
			}


		 	games.push_back(g);
		}

		mapGames.push_back(games);
	}

	for (int i = 0; i < numberOfMaps; i++) {
		
	}
}

static string select_map_()
{
	bool valid_input = false;
	int input;

	DIR *pDIR;
	struct dirent *entry;
	int count = 0;
	vector<string> files;

	cout << "\n\n***Available maps***" << endl;
	if (pDIR = opendir("./maps/"))
	{
		while (entry = readdir(pDIR))
		{
			if (strcmp(entry->d_name, ".") != 0 &&
			    strcmp(entry->d_name, "..") != 0 &&
			    entry->d_name[strlen(entry->d_name) - 2] == 'a')
			{
				files.push_back(entry->d_name);
				cout << ++count << "- " << entry->d_name << "\n";
			}
		}
		closedir(pDIR);
	}
	while (!valid_input)
	{
		cout << "Which map would you like to use? (enter number)" << endl;
		cin >> input;
		if ((input >= 1) && (input <= count))
		{
			valid_input = true;
		}
		else
		{
			cin.clear();
			cin.ignore(100, '\n');
			cerr << "invalid input !!" << endl;
		}
	}
	return "./maps/" + files.at(input - 1);
}
