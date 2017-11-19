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

#define ARRAY_SIZE(array) (sizeof((array)) / sizeof((array[0])))

using namespace std;

int main()
{
	displayLogo();
	start_game();

	Map *map = loadMap();

	int countriesCount = 0;
	vector<Continent *> continents = map->getContinents();
	for (int i = 0; i < continents.size(); i++)
	{
		countriesCount += continents[i]->getCountries().size();
	}

	Deck *deck = createDeck(countriesCount);

	vector<Player *> players = createPlayers();

	cout << "\n\n===\nMAP:\n===\n";
	for (int i = 0; i < continents.size(); i++)
	{
		cout << "CONTINENT: " << continents[i]->name << "\n------------------------\n";
		vector<Country *> countries = continents[i]->getCountries();
		for (int j = 0; j < countries.size(); j++)
		{
			cout << countries[j]->name << ": ";
			vector<Country *> neighbors = countries[j]->getNeighbors();
			for (int k = 0; k < neighbors.size(); k++)
			{
				cout << neighbors[k]->name << ", ";
			}
			cout << "\n";
		}
		cout << "\n";
	}
        //Distribute countries between players
	int num_player=players.size();
	int index = 0;
	for (std::vector<Continent *>::iterator it = continents.begin(); it != continents.end(); ++it)
	{
		vector<Country *> countries = (*it)->getCountries();
		for (std::vector<Country *>::iterator it2 = countries.begin(); it2 != countries.end(); ++it2)
		{
			players.at(index)->addCountry((*it2));
			(*it2)->owner = (players.at(index));
			index = (index + 1) % num_player;
		}
	}

	cout << "\n\n=======\nPLAYERS:\n=======\n";
	for (int i = 0; i < players.size(); i++)
	{
		printPlayerInfo(players[i]);
	}

	cout << "\n\n====\nDECK:\n====\nCreated " << countriesCount - (countriesCount % 3) << " card deck\n";

	players[1]->getHand()->drawCard(deck);
	players[1]->getHand()->drawCard(deck);
	players[1]->getHand()->drawCard(deck);
	players[1]->getHand()->drawCard(deck);
	players[1]->getHand()->drawCard(deck);
	players[1]->getHand()->drawCard(deck);
	players[1]->getHand()->drawCard(deck);
	players[1]->getHand()->drawCard(deck);
	players[1]->getHand()->drawCard(deck);
	players[1]->getHand()->drawCard(deck);
	players[1]->getHand()->drawCard(deck);
	players[1]->getHand()->drawCard(deck);
	players[1]->getHand()->drawCard(deck);
	players[1]->getHand()->drawCard(deck);
	players[1]->getHand()->drawCard(deck);
	players[1]->getHand()->drawCard(deck);
	players[1]->getHand()->drawCard(deck);
	players[1]->getHand()->drawCard(deck);
	reinforcementPhase(players[1], map);
	cout << players[1]->getArmies() << endl;

	return 0;
}
