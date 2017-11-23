
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
	cout << "Turn number: " << game->getTurnNumber() << endl;
}

ObserverDecorator::ObserverDecorator(AbstractObserver *obs) {
	wrapped_obs = obs;
}

void ObserverDecorator::info(Game *game) {
	wrapped_obs->info(game);
}

PlayerDominationObserver::PlayerDominationObserver(ObserverDecorator *obs): ObserverDecorator(obs) {}

void PlayerDominationObserver::info(Game *game) {
	ObserverDecorator::info(game);
	
	int totalCountries = game->getMap()->countryCount();
	
	for (int i = 0; i < game->get_players().size(); i++) {
		int percentage = game->get_players()[i]->getCountries().size() / totalCountries * 100;
		cout << "Player " << i << " owns " << percentage << "% of all countries" << endl;
	}
}

PlayerHandObserver::PlayerHandObserver(ObserverDecorator *obs): ObserverDecorator(obs) {}

void PlayerHandObserver::info(Game *game) {
	ObserverDecorator::info(game);
	
	for (int i = 0; i < game->get_players().size(); i++) {
		Hand *hand = game->get_players()[i]->getHand();
		cout << "Player " << i << "'s hand: "
		     << hand->infantrySize() << " infantries, "
		     << hand->cavalerySize() << " cavaleries, "
		     << hand->artillerySize() << " artilleries" << endl;
	}
}

ContinentControlObserver::ContinentControlObserver(ObserverDecorator *obs): ObserverDecorator(obs) {}

void ContinentControlObserver::info(Game *game) {
	ObserverDecorator::info(game);
	
	vector<Continent *> continents = game->getMap()->getContinents();
	// Map continent ->* player <-> ownership
	map<string, map<int, int>> ownership;
	
	for (int i = 0; i < continents.size(); i++) {
		map<int, int> continentOwnership;

		for (int j = 0; j < continents[i]->getCountries().size(); j++) {
			
		}
	}

	for (int i = 0; i < continents.size(); i++) {

	}
}
