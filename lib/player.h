#ifndef PLAYER_H
#define PLAYER_H


#include <vector>
#include <string>
#include <iostream>

#include "map.h"
#include "dice.h"
#include "card.h"

using namespace std;

class Player {
public:
	string name;
	Player(string name, int numberOfDices);
	Player(string name, int numberOfDices, int initArmies);

	int getArmies();
	void setArmies(int newArmies);
	
	bool reinforce(Country* country, int reinforcement);
	void attack();
	void fortify();

	Hand *getHand();
	Dice *getDice();
	vector<Country *> getCountries();
	void addCountry(Country* country);
	bool hasCountry(Country* country);
	bool hasCountry(string name);
private:
	int armies;
	Hand *hand;
	Dice *dice;
	vector<Country *> countries;
};

#endif
