
#include <typeinfo>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <fstream>
#include <dirent.h>
#include <vector>
#include <ctime>

#include "Maploader.h"
#include "game.h"
#include "player.h"

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
	turnNumber++;
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
	int totalCountries = 0;
	for (int i = 0; i < players.size(); i++)
	{
		totalCountries += players[i]->getCountries().size();
	}

	if (totalCountries == players[currentPlayer]->getCountries().size())
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
	this->map = map;
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

void Game::createDeck(int countries)
{
	Deck *d = new Deck(countries);
	deck = d;
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
			cout << "4) Random Computer" << endl;
			cout << "5) Cheater Computer" << endl;
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
			case 4:
				players.push_back(new RandomComputer("Player " + to_string(i + 1), 3));
				valid_input = true;
				break;
			case 5:
				players.push_back(new CheaterComputer("Player " + to_string(i + 1), 3));
				valid_input = true;
				break;
			default:
				break;
			}
		}
	}
	this->players = players;
}

// Computer players
void Game::createPlayers(int numOfPlayers)
{
	vector<Player *> players;
	
	for (int i = 0; i < numOfPlayers; i++) {
		int type = rand() % 2 + 1;

		switch (type) {
		case 1:
			players.push_back(new AggressiveComputer("Player " + to_string(i + 1), 3));
			break;
		case 2:
			players.push_back(new BenevolentComputer("Player " + to_string(i + 1), 3));
			break;
		default:
			break;
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
	Player *player = this->players.at(this->currentPlayer);
	notify_current_player();
	notify_current_phase("Reinforcement");

	if (player->type == 0)
	{
		static_cast<Human *>(player)->reinforce(this->map);
	}
	else if (player->type == 1)
	{
		static_cast<AggressiveComputer *>(player)->reinforce(this->map);
	}
	else if (player->type == 2)
	{
		static_cast<BenevolentComputer *>(player)->reinforce(this->map);
	}	
	else if (player->type == 3)
	{
		static_cast<RandomComputer *>(player)->reinforce(this->map);
	}
	else if (player->type == 4)
	{
		static_cast<CheaterComputer *>(player)->reinforce(this->map);
	}

	notify_msg("Reinforcement phase over");
}

void Game::attackPhase()
{
	Player *player = this->players.at(this->currentPlayer);
	notify_current_player();
	notify_current_phase("Attack");
	if (player->type == 0)
	{
		static_cast<Human *>(player)->attack();
	}
	else if (player->type == 1)
	{
		static_cast<AggressiveComputer *>(player)->attack();
	}
	else if (player->type == 2)
	{
		static_cast<BenevolentComputer *>(player)->attack();
	}	
	else if (player->type == 3)
	{
		static_cast<RandomComputer *>(player)->attack();
	}
	else if (player->type == 4)
	{
		static_cast<CheaterComputer *>(player)->attack();
	}
	notify_msg("Attack phase over");
}

void Game::fortificationPhase()
{
	Player *player = this->players.at(this->currentPlayer);
	notify_current_player();
	notify_current_phase("Fortification");

	if (player->type == 0)
	{
		static_cast<Human *>(player)->fortify();
	}
	else if (player->type == 1)
	{
		static_cast<AggressiveComputer *>(player)->fortify();
	}
	else if (player->type == 2)
	{
		static_cast<BenevolentComputer *>(player)->fortify();
	}
	else if (player->type == 3)
	{
		static_cast<RandomComputer *>(player)->fortify();
	}
	else if (player->type == 4)
	{
		static_cast<CheaterComputer *>(player)->fortify();
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

void Game::register_observer(AbstractObserver *observer)
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

void Game::notify_game_stats()
{
	for (int i = 0; i < observers.size(); i++)
	{
		observers[i]->print_game_stats(players);
	}
}

vector<Player *> Game::get_players()
{
	return players;
}

int Game::getTurnNumber()
{
	return turnNumber;
}

Map *Game::getMap()
{
	return map;
}

Deck *Game::getDeck()
{
	return deck;
}
