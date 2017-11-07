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
	bool attack(Country* attacker, Country* defender,int attackerDiceCount,int defenderDiceCount);
	bool fortify(Country* source,Country* target, int fortificationAmount);

	Hand *getHand();
	Dice *getDice();
	vector<Country *> getCountries();
	void addCountry(Country* country);
	void removeCountry(Country* country);
	bool hasCountry(Country* country);
	bool hasCountry(string name);
	int numOfContinents(Map *map);
private:
	int armies;
	Hand *hand;
	Dice *dice;
	vector<Country *> countries;
};

#endif
