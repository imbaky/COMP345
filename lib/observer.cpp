
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


void Observer::info(Game *game) {
	cout << "BASIC OBSERVER:" << endl;
	cout << "===============" << endl;
	cout << "Turn number: " << game->getTurnNumber() << endl;
	cout << endl;
}

ObserverDecorator::ObserverDecorator(AbstractObserver *obs) { wrapped_obs = obs; }
void ObserverDecorator::notify(string msg) { wrapped_obs->notify(msg); }
void ObserverDecorator::print_game_stats(vector<Player *> players) { wrapped_obs->print_game_stats(players); }
void ObserverDecorator::info(Game *game) { wrapped_obs->info(game); }


PlayerDominationObserver::PlayerDominationObserver(AbstractObserver *obs): ObserverDecorator(obs) {}

void PlayerDominationObserver::info(Game *game) {
	ObserverDecorator::info(game);
	cout << "PLAYER DOMINATION OBSERVER:" << endl;
	cout << "===========================" << endl;
		
	vector<Player *> players = game->get_players();
	// Chart bars have 50 '='
	// [==================================================]
	// Player 0: [========================================          ] 90% -> 
	// Player 1: [===========                                       ] 10% -> 
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

PlayerHandObserver::PlayerHandObserver(AbstractObserver *obs): ObserverDecorator(obs) {}

void PlayerHandObserver::info(Game *game) {
	ObserverDecorator::info(game);
	cout << "PLAYER HAND OBSERVER:" << endl;
	cout << "=====================" << endl;
	
	for (int i = 0; i < game->get_players().size(); i++) {
		Hand *hand = game->get_players()[i]->getHand();
		cout << "Player " << i << "'s hand: "
		     << hand->infantrySize() << " infantries, "
		     << hand->cavalerySize() << " cavaleries, "
		     << hand->artillerySize() << " artilleries" << endl;
	}

	cout << endl;
}

ContinentControlObserver::ContinentControlObserver(AbstractObserver *obs): ObserverDecorator(obs) {}

void ContinentControlObserver::info(Game *game) {
	ObserverDecorator::info(game);
	cout << "CONTINENT CONTROL OBSERVER:" << endl;
	cout << "===========================" << endl;
	
	vector<Continent *> continents = game->getMap()->getContinents();
	// Map continent ->* player <-> ownership
	map<string, map<string, int>> ownership;
	
	for (int i = 0; i < continents.size(); i++) {
		map<string, int> continentOwnership;

		for (int j = 0; j < continents[i]->getCountries().size(); j++) {
			continentOwnership[continents[i]->getCountries()[j]->owner->name]++;
		}

		cout << "Ownership of " << continents[i]->name << endl;
		map<string, int>::iterator it;
		for ( it = continentOwnership.begin(); it != continentOwnership.end(); it++ ) {
			cout << it->first << ": "
			     << it->second
			     << "/"
			     << continents[i]->getCountries().size()
			     << endl;
		}
	}
		
	cout << endl;
}
