
#include <iostream>

#include "tournament.h"

void Tournament::start() {
	setup();
}

void Tournament::setup() {
	bool valid_input = false;
	int numberOfMaps, numberOfComputers, numberOfGames, numberOfTurns;

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
		cout << "Select the number of computers (1-5 players)" << endl;
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
		cout << "Select the number of computers (1-5 players)" << endl;
		cin >> numberOfTurns;
		if ((numberOfTurns >= 1) && (numberOfTurns <= 5))
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
}

