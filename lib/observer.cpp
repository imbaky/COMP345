
#include <vector>
#include <string>

#include "observer.h"
#include "game.h"
#include "player.h"

using namespace std;


Observer::Observer() {}

void Observer::notify(string msg) {
	cout << "Msg from observable => " << msg << endl;
}

void Observer::print_game_stats(vector<Player *> players) {
	// Chart bars have 50 '='
	// [==================================================]
	// Player 0: [========================================          ] 90% -> 
	// Player 1: [===========                                       ] 10% -> 
	cout << endl;
	cout << "----------------------------" << endl;
	cout << "-- World Domination State --" << endl;
	cout << "----------------------------" << endl;
	
	int totalCountries = 0;
	vector<int> individualPlayerCount;
	for (int i = 0; i < players.size(); i++) {
		individualPlayerCount.push_back(players[i]->getCountries().size());
		totalCountries += players[i]->getCountries().size();
	}
	
	for (int i = 0; i < individualPlayerCount.size(); i++) {
		int percentageOwned = individualPlayerCount[i] * 100 / totalCountries;
		int length = percentageOwned * 50 / 100;
		
		cout << "Player " << i << ": " << "[";
		for (int j = 0; j < length; j++) {
			cout << "=";
		}
		for (int j = 0; j < 50 - length; j++) {
			cout << " ";
		}
		cout << "] " << percentageOwned << "% -> "
		     << individualPlayerCount[i] << " countries, " << endl;
	}
	cout << endl;
}
