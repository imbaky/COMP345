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

#define ARRAY_SIZE(array) (sizeof((array)) / sizeof((array[0])))

using namespace std;

// function declaration
void start_game();
string select_map();
int players_number();

Map *loadMap()
{
	MapLoader *ml = new MapLoader();
	do
	{
		ml->loadMap(select_map());
	} while (!ml->isValid());

	Map *map = ml->getMap();
	return map;
}

Deck *createDeck(int countries)
{
	Deck *deck = new Deck(countries);
	return deck;
}

vector<Player *> createPlayers()
{
	int playerCount = players_number();
	vector<Player *> players;
	for (int i = 0; i < playerCount; i++)
	{
		Player *newPlayer = new Player("Player " + to_string(i + 1), 3);
		players.push_back(newPlayer);
	}
	return players;
}

void start_game()
{
	bool valid_input = false;
	char input;
	while (!valid_input)
	{
		cout << "Would you like to start the game? (y/n)" << endl;
		cin >> input;
		if (input == 'y')
		{
			valid_input = true;
		}
		else if (input != 'n')
			cerr << "invalid input !!" << endl;
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
		else{
			cin.clear();
			cin.ignore(100,'\n');
			cerr << "invalid input !!" << endl;

		}
			
	}
	return "./maps/" + files.at(input - 1);
}

int players_number()
{
	bool valid_input = false;
	int input;
	while (!valid_input)
	{
		cout << "Select the number of players in the game (2-6 players)" << endl;
		cin >> input;
		if ((input >= 2) && (input <= 6))
		{
			valid_input = true;
		}
		else{
			cin.clear();
			cin.ignore(100,'\n');
			cerr << "invalid input !!" << endl;
		}

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

	while (!validInput)
	{
		cout << "Exchange cards? (y/n)\n";
		cin >> input;
		if (input == 'y')
		{
			cout << "(0) Echange infantries\n";
			cout << "(1) Echange cavaleries\n";
			cout << "(2) Echange artilleries\n";
			cout << "(3) Echange all\n";
			cin >> input;
			switch (input)
			{
			case '0':
				additionalArmies += player->getHand()->exchange(Infantry);
				validInput = true;

				break;
			case '1':
				additionalArmies += player->getHand()->exchange(Cavalery);
				validInput = true;

				break;
			case '2':
				additionalArmies += player->getHand()->exchange(Artillery);
				validInput = true;

				break;
			case '3':
				additionalArmies += player->getHand()->exchange();
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
	cout << player->name << " gets " << additionalArmies << " armies" << endl;
	vector<Country *> countries = player->getCountries();
	cout << "The player's armies will be distrubuted equally among their countries" << endl;
	for (int i = 0; i < additionalArmies; i++)
	{
		player->reinforce(countries.at(i % countries.size()), 1);

	}
	//prints all countries that th eplayer owns with army sizes
	for (int i = 0; i < countries.size(); i++)
	{
	cout << countries.at(i)->name << " now has "
	<< countries.at(i)->getArmySize()
	<< " armies " << endl;
	}
}

void attackPhase(Player *player)
{
	char input;
	bool validInput = false;
	while (!validInput)
	{
		cout << "Attack? (y/n)\n";
		cin >> input;
		if (input == 'y')
		{
			// Hash of the countries and neightbors it can attack
			map<string, vector<Country *>> validCountries;
			// A player's countries
			vector<Country *> countries = player->getCountries();

			cout << "Select a country that you would like to attack from:" << endl;
			for (int i = 0; i < player->getCountries().size(); i++)
			{
				cout << i << "- " << player->getCountries().at(i)->name << " Army size:" << player->getCountries().at(i)->getArmySize() << endl;
			}
			int attackCountry;
			cin >> attackCountry;

			vector<Country *> neighbors;
			for (int i = 0; i < player->getCountries().at(attackCountry)->getNeighbors().size(); i++)
			{
				if (static_cast<Player *>(player->getCountries().at(attackCountry)->getNeighbors().at(i)->owner)->name != static_cast<Player *>(player->getCountries().at(attackCountry)->owner)->name)
					neighbors.push_back(player->getCountries().at(attackCountry)->getNeighbors().at(i));
			}

			cout << "Select a neighboring country that you would like to attack:" << endl;
			for (int i = 0; i < neighbors.size(); i++)
			{
				cout << i << "- " << neighbors.at(i)->name << " Army size:" <<neighbors.at(i)->getArmySize() << endl;
			}
			int enemyCountry;
			cin >> enemyCountry;

			int attackerDices, defenderDices;

			cout << static_cast<Player *>(player->getCountries().at(attackCountry)->owner)->name << " Number of dices to attack (1, 2 or 3)?" << endl;
			cin >> attackerDices;

			cout << static_cast<Player *>(neighbors.at(enemyCountry)->owner)->name << " Number of dices to defend (1 or 2)?" << endl;
			cin >> defenderDices;

			if (player->attack(player->getCountries().at(attackCountry), neighbors.at(enemyCountry), attackerDices, defenderDices))
			cout<<"Attack successful!!"<<endl;
			else
			{
				validInput = false;
				cout << "invalid input";
			}
		}
		if (input == 'n')
			validInput = true;
	}
}

void fortificationPhase(Player *player)
{
	char input;
	bool validInput = false;
	while (!validInput)
	{
		cout << "Fortify? (y/n)\n";
		cin >> input;
		if (input == 'y')
		{
			cout << "Select one of your countries that you would like to fortify:" << endl;
			for (int i = 0; i < player->getCountries().size(); i++)
			{
				cout << i << "- " << player->getCountries().at(i)->name << " Army size:" << player->getCountries().at(i)->getArmySize() << endl;
			}
			int targetCountry;
			cin >> targetCountry;

			if ((targetCountry < 0) || (targetCountry > player->getCountries().size()))
			{
				continue;
			}

			vector<Country *> neighbors;
			for (int i = 0; i < player->getCountries().at(targetCountry)->getNeighbors().size(); i++)
			{
				if (static_cast<Player *>(player->getCountries().at(targetCountry)->getNeighbors().at(i)->owner)->name == static_cast<Player *>(player->getCountries().at(targetCountry)->owner)->name)
					neighbors.push_back(player->getCountries().at(targetCountry)->getNeighbors().at(i));
			}

			cout << "Select a neighboring country that you want to move armies from:" << endl;
			for (int i = 0; i < neighbors.size(); i++)
			{
				cout << i << "- " << neighbors.at(i)->name << " Army size:" << neighbors.at(i)->getArmySize() << endl;
			}
			int sourceCountry;
			cin >> sourceCountry;

			cout << "How much of your army would you like to move ?" << endl;
			int fortificationAmount;
			cin >> fortificationAmount;

			if(player->fortify(neighbors.at(sourceCountry) ,player->getCountries().at(targetCountry),fortificationAmount))
			{
				validInput = true;
				cout<<"--- Your countries after fortification----"<<endl;
				for (int i = 0; i < player->getCountries().size(); i++)
				{
					cout << i << "- " << player->getCountries().at(i)->name << " Army size:" << player->getCountries().at(i)->getArmySize() << endl;
				}
			}
			else{
				cout<<"Invalid move"<<endl;
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

	for (int i = 0; i < continents.size(); i++)
	{
		vector<Country *> continentCountries = continents[i]->getCountries();
		for (int j = 0; j < continentCountries.size(); j++)
		{
			vector<Country *>::iterator it = find(countries.begin(), countries.end(), continentCountries[j]);
			if (it == countries.end())
			{
				break;
			}
			if (j == continentCountries.size() - 1)
			{
				owned++;
			}
		}
	}

	return owned;
}

void printPlayerInfo(Player *player)
{
	cout << player->name << ": " << player->getDice()->getDices().size() << " dices, "
	     << player->getArmies() << " armies\n";
}

void displayLogo()
{
	cout << "██████╗ ██╗███████╗██╗  ██╗\n"
	     << "██╔══██╗██║██╔════╝██║ ██╔╝\n"
	     << "██████╔╝██║███████╗█████╔╝ \n"
	     << "██╔══██╗██║╚════██║██╔═██╗ \n"
	     << "██║  ██║██║███████║██║  ██╗\n"
	     << "╚═╝  ╚═╝╚═╝╚══════╝╚═╝  ╚═╝\n\n"
	     << endl;
}
