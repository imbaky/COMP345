#include "game.h"
#include "Maploader.h"
#include "player.h"
#include <typeinfo>

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <fstream>
#include <dirent.h>
#include <vector>

using namespace std;

Game *Game::getInstance()
{
	static Game *instance = nullptr;
	if (instance == nullptr)
	{
		instance = new Game();
	}
	return instance;
}

void Game::turn()
{
	this->reinforcementPhase();
	this->attackPhase();
	this->fortificationPhase();
}

void Game::nextTurn()
{
	currentPlayer = (currentPlayer + 1) % players.size();
}

bool Game::setPlayers(vector<Player *> players)
{
	this->players = players;
}

Player *Game::getCurrentPlayer()
{
	return this->players.at(this->currentPlayer);
}

bool Game::setMap(Map *map)
{
	this->map = map;
}

bool Game::hasWon()
{
	if (this->map->countryCount() == this->players.at(this->currentPlayer)->getCountries().size())
	{
		return true;
	}
	return false;
}

Map *Game::loadMap()
{
	MapLoader *ml = new MapLoader();
	do
	{
		ml->loadMap(select_map());
	} while (!ml->isValid());

	Map *map = ml->getMap();
	return map;
}

string Game::select_map()
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

Deck *Game::createDeck(int countries)
{
	Deck *deck = new Deck(countries);
	return deck;
}

void Game::createPlayers()
{
	int playerCount = players_number();
	vector<Player *> players;

	for (int i = 0; i < playerCount; i++)
	{
		bool valid_input = false;
		int input;
		while (!valid_input)
		{
			cout << "What type of player should Player " + to_string(i + 1) + ", choose 1, 2 or 3"
			     << " be ?" << endl;
			cout << "1) Human" << endl;
			cout << "2) Agressive Computer" << endl;
			cout << "3) Benevolent Computer" << endl;
			cin >> input;
			switch (input)
			{
			case 1:
				players.push_back(new Human("Player " + to_string(i + 1), 3));
				valid_input = true;
				break;
			case 2:
				players.push_back(new AggressiveComputer("Player " + to_string(i + 1), 3));
				valid_input = true;
				break;
			case 3:
				players.push_back(new BenevolentComputer("Player " + to_string(i + 1), 3));
				valid_input = true;
				break;
			default:
				break;
			}
		}
	}
	this->players = players;
}

void Game::start_game()
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

int Game::players_number()
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
		else
		{
			cin.clear();
			cin.ignore(100, '\n');
			cerr << "invalid input !!" << endl;
		}
	}
	return input;
}

void Game::reinforcementPhase()
{
	notify_current_player();
	notify_current_phase("Reinforcement");
	Player *player = this->players.at(this->currentPlayer);

	vector<Country *> countries = player->getCountries();

	char input;
	bool validInput = false;
	int owned = player->getCountries().size();

	int additionalArmies = owned / 3;
	if (additionalArmies < 3)
		additionalArmies = 3;

	additionalArmies += player->numOfContinents(this->map);
	if (player->type == 0)
	{

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
					notify_msg("Player " + to_string(currentPlayer) + "exchanged his infantry for " +
						   to_string(additionalArmies) + "armies.");
					validInput = true;

					break;
				case '1':
					additionalArmies += player->getHand()->exchange(Cavalery);
					notify_msg("Player " + to_string(currentPlayer) + "exchanged his cavalery for " +
						   to_string(additionalArmies) + "armies.");
					validInput = true;

					break;
				case '2':
					additionalArmies += player->getHand()->exchange(Artillery);
					notify_msg("Player " + to_string(currentPlayer) + "exchanged his artillery for " +
						   to_string(additionalArmies) + "armies.");
					validInput = true;

					break;
				case '3':
					additionalArmies += player->getHand()->exchange();
					notify_msg("Player " + to_string(currentPlayer) + "exchanged his cards for " +
						   to_string(additionalArmies) + "armies.");
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

		cout << "The player's armies will be distrubuted equally among their countries" << endl;
		for (int i = 0; i < additionalArmies; i++)
		{
			player->reinforce(countries.at(i % countries.size()), 1);
		}
	}
	else if (player->type == 1)
	{
		additionalArmies += player->getHand()->exchange();
		cout << player->name << " gets " << additionalArmies << " armies" << endl;
		Country *strongestCountry = countries.at(0);
		for (int i = 0; i < countries.size(); i++)
		{
			if ((countries.at(i)->getArmySize() >= strongestCountry->getArmySize()))
			{
				for (int j = 0; j < countries.at(i)->getNeighbors().size(); j++)
				{
					if (static_cast<Player *>(countries.at(i)->getNeighbors().at(j)->owner)->name == static_cast<Player *>(countries.at(i)->owner)->name)
					{
						strongestCountry = countries.at(i);
						break;
					}
				}
			}
		}
		player->reinforce(strongestCountry, additionalArmies);
	}
	else if (player->type == 2)
	{
		additionalArmies += player->getHand()->exchange();
		cout << player->name << " gets " << additionalArmies << " armies" << endl;
		Country *weakestCountry = countries.at(0);
		for (int i = 0; i < countries.size(); i++)
		{
			if ((countries.at(i)->getArmySize() <= weakestCountry->getArmySize()))
			{
				for (int j = 0; j < countries.at(i)->getNeighbors().size(); j++)
				{
					if (static_cast<Player *>(countries.at(i)->getNeighbors().at(j)->owner)->name == static_cast<Player *>(countries.at(i)->owner)->name)
					{
						weakestCountry = countries.at(i);
						break;
					}
				}
			}
		}
		player->reinforce(weakestCountry, additionalArmies);
	}

	//prints all countries that th eplayer owns with army sizes
	for (int i = 0; i < countries.size(); i++)
	{
		cout << countries.at(i)->name << " now has "
		     << countries.at(i)->getArmySize()
		     << " armies " << endl;
	}

	notify_msg("Reinforcement phase over");
	notify_game_stats();
}

void Game::attackPhase()
{
	Player *player = this->players.at(this->currentPlayer);
	notify_current_player();
	notify_current_phase("Attack");
	if (player->type == 0)
	{
	static_cast<Human*>(player)->attack();	
	}
	else if (player->type == 1)
	{
	}
	else if (player->type == 2)
	{

	}
	notify_msg("Attack phase over");
	notify_game_stats();
}

void Game::fortificationPhase()
{
	Player *player = this->players.at(this->currentPlayer);
	notify_current_player();
	notify_current_phase("Fortification");

	if (player->type == 0)
	{
	static_cast<Human*>(player)->fortify();	
	}
	else if (player->type == 1)
	{
	}
	else if (player->type == 2)
	{
	}
	notify_msg("Fortification phase over");
	notify_game_stats();
}

void Game::printPlayerInfo(Player *player)
{
	cout << player->name << ": " << player->getDice()->getDices().size() << " dices, "
	     << player->getArmies() << " armies\n";
}

void Game::displayLogo()
{
	cout << "██████╗ ██╗███████╗██╗  ██╗\n"
	     << "██╔══██╗██║██╔════╝██║ ██╔╝\n"
	     << "██████╔╝██║███████╗█████╔╝ \n"
	     << "██╔══██╗██║╚════██║██╔═██╗ \n"
	     << "██║  ██║██║███████║██║  ██╗\n"
	     << "╚═╝  ╚═╝╚═╝╚══════╝╚═╝  ╚═╝\n\n"
	     << endl;
}

void Game::register_observer(Observer *observer)
{
	if (find(observers.begin(), observers.end(), observer) != observers.end())
	{
		return;
	}
	observers.push_back(observer);
}

void Game::notify_current_player()
{
	for (int i = 0; i < observers.size(); i++)
	{
		observers[i]->notify("Current Player: " + to_string(currentPlayer));
	}
}

void Game::notify_current_phase(string phase)
{
	for (int i = 0; i < observers.size(); i++)
	{
		observers[i]->notify("Current Phase: " + phase);
	}
}

void Game::notify_msg(string msg)
{
	for (int i = 0; i < observers.size(); i++)
	{
		observers[i]->notify(msg);
	}
}

void Game::notify_game_stats() {
	for (int i = 0; i < observers.size(); i++)
	{
		observers[i]->print_game_stats(players);
	}
}

vector<Player *> Game::get_players()
{
	return players;
}
