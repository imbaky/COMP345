#ifndef PLAYER_H
#define PLAYER_H


#include <vector>
#include <string>

#include "map.h"
#include "dice.h"
#include "card.h"

using namespace std;

class Player {
public:
	string name;
	Player(string name, int numberOfDices);
	
	void reinforce();
	void attack();
	void fortify();

	Hand *getHand();
	Dice *getDice();
	vector<Country *> getCountries();
	void addCountry(Country* country);
private:
	Hand *hand;
	Dice *dice;
	vector<Country *> countries;

};

#endif
