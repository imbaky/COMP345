
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

	string maps[numberOfMaps];
	Game *games[numberOfMaps][numberOfGames];
	string results[numberOfMaps][numberOfGames];

	AbstractObserver *observers[numberOfMaps][numberOfGames];

	cout << "TOURNAMENT\n" << "==========\n"
	     << "Number of maps: " << numberOfMaps << "\n"
	     << "Number of games per map: " << numberOfGames << "\n"
	     << "Number of players: " << numberOfComputers << "\n"
	     << "Number of turns per game: " << numberOfTurns << endl;

	for (int i = 0; i < numberOfMaps; ++i) {
		maps[i] = select_map_();
	}

	for (int i = 0; i < numberOfMaps; ++i) {
		cout << maps[i] << " ";
		for (int j = 0; j < numberOfGames; ++j) {
			games[i][j] = new Game();

			observers[i][j] = new Observer();
			games[i][j]->register_observer(observers[i][j]);

			MapLoader *ml = new MapLoader();
			ml->loadMap(maps[i]);
			Map *map = ml->getMap();

			int countriesCount = 0;
			vector<Continent *> continents = map->getContinents();
			for (int k = 0; k < continents.size(); k++) {
				countriesCount += continents[k]->getCountries().size();
			}

			games[i][j]->createDeck(countriesCount);
			games[i][j]->createPlayers(numberOfComputers);

			//Distribute countries between players
			int num_player = games[i][j]->get_players().size();
			int index = 0;
			for (std::vector<Continent *>::iterator it = continents.begin(); it != continents.end(); ++it)
			{
				vector<Country *> countries = (*it)->getCountries();
				for (std::vector<Country *>::iterator it2 = countries.begin(); it2 != countries.end(); ++it2)
				{
					games[i][j]->get_players().at(index)->addCountry((*it2));


					(*it2)->owner = (games[i][j]->get_players().at(index));
					index = (index + 1) % num_player;
				}
			}

			int initial_army = 40 - ((num_player - 2) * 5);
			//Distribute a players armies among their countries
			for (int k = 0; k < games[i][j]->get_players().size(); k++) {
				int army_available = initial_army;
				vector<Country *> countries = games[i][j]->get_players()[k]->getCountries();

				while (army_available > 0)
					for (int l = 0; l < countries.size(); l++) {
						if (army_available-- > 0) {
							countries[l]->setArmySize((countries[l]->getArmySize()) + 1);
						}
						else
							break;
					}
			}
		}
	}

	cout << "STARTING TOURNAMENT..." << endl;

	for (int i = 0; i < numberOfMaps; ++i) {
		for (int j = 0; j < numberOfGames; ++j) {
			while (!games[i][j]->hasWon() && games[i][j]->getTurnNumber() <= numberOfTurns) {
				games[i][j]->getCurrentPlayer()->getHand()->drawCard(games[i][j]->getDeck());
				games[i][j]->reinforcementPhase();
				games[i][j]->attackPhase();
				games[i][j]->fortificationPhase();
				games[i][j]->nextTurn();
				observers[i][j]->info(games[i][j]);
				cout << "====================================================================" << endl;
			}
			if (games[i][j]->getTurnNumber() > numberOfTurns) {
				
				results[i][j] = "Draw";
			} else {

				switch (games[i][j]->getCurrentPlayer()->type) {
				case 1:
					results[i][j] = "Aggressive";
					break;
				case 2:
					results[i][j] = "Benevolent";
					break;
				default:
					break;
				}
			}
		}
	}


	cout << "RESULTS\n" << "=======\n";
	for (int i = 0; i < numberOfMaps; ++i) {
		for (int j = 0; j < numberOfGames; ++j) {
			cout << results[i][j] << "  ";
		}
		cout << endl;
	}
}

void Tournament::setup() {
	bool valid_input = false;
	int numberOfMaps, numberOfComputers, numberOfGames, numberOfTurns;

	while (!valid_input) {
		cout << "Select the number of maps (1-5 players)" << endl;
		cin >> numberOfMaps;
		if ((numberOfMaps >= 1) && (numberOfMaps <= 5))
		{
			this->numberOfMaps = numberOfMaps;
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
			this->numberOfComputers = numberOfComputers;
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
			this->numberOfGames = numberOfGames;
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
			this->numberOfTurns = numberOfTurns;
			valid_input = true;
		}
		else
		{
			cin.clear();
			cin.ignore(100, '\n');
			cerr << "invalid input !!" << endl;
		}
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
