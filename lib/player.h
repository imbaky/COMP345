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

	int getArmies();
	void setArmies(int newArmies);
	
	void reinforce();
	void attack();
	void fortify();

	Hand *getHand();
	Dice *getDice();
	vector<Country *> getCountries();
	void addCountry(Country* country);
private:
	int armies;
	Hand *hand;
	Dice *dice;
	vector<Country *> countries;
};

#endif
