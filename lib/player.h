#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <iostream>

#include "map.h"
#include "dice.h"
#include "card.h"
#include "observer.h"

using namespace std;

class Player
{

      public:
	enum PlayerType
	{
		Human,
		AggressiveComputer,
		BenevolentComputer
	};
	string name;
	int type;
	Player(string name, int numberOfDices);
	Player(string name, int numberOfDices, int initArmies);

	int getArmies();
	void setArmies(int newArmies);

	bool reinforce(Country *country, int reinforcement);
	bool attack(Country *attacker, Country *defender, int attackerDiceCount, int defenderDiceCount);
	bool fortify(Country *source, Country *target, int fortificationAmount);
	Country *getStrongestCountry();
	Hand *getHand();
	Dice *getDice();
	vector<Country *> getCountries();
	void addCountry(Country *country);
	void removeCountry(Country *country);
	bool hasCountry(Country *country);
	bool hasCountry(string name);
	int numOfContinents(Map *map);

private:

	int armies;
	Hand *hand;
	Dice *dice;
	vector<Country *> countries;
};

class Human : public Player
{
      public:
	Human(string name, int numberOfDices) : Player(name, numberOfDices){ this->type=0;};
	Human(string name, int numberOfDices, int initArmies) : Player(name, numberOfDices, initArmies){this->type=0;};

	bool reinforce(Map* map);
	bool attack();
	bool fortify();
};

class AggressiveComputer : public Player
{
      public:
	AggressiveComputer(string name, int numberOfDices) : Player(name, numberOfDices){this->type=1;};
	AggressiveComputer(string name, int numberOfDices, int initArmies) : Player(name, numberOfDices, initArmies){this->type=1;};

	bool reinforce(Map* map);
	bool attack();
	bool fortify();
};

class BenevolentComputer : public Player
{
      public:
	BenevolentComputer(string name, int numberOfDices) : Player(name, numberOfDices){this->type=2;};
	BenevolentComputer(string name, int numberOfDices, int initArmies) : Player(name, numberOfDices, initArmies){this->type=2;};

	bool reinforce(Map* map);
	bool attack();
	bool fortify();
};
#endif
