#include "player.h"

Player::Player(string playerName, int numberOfDices)
{
	name = playerName;
	hand = new Hand();
	dice = new Dice(numberOfDices);
	armies = 0;
}

Player::Player(string playerName, int numberOfDices, int initArmies)
{
	name = playerName;
	hand = new Hand();
	dice = new Dice(numberOfDices);
	armies = initArmies;
}

int Player::getArmies()
{
	return armies;
}

void Player::setArmies(int newArmies)
{
	armies = newArmies;
}

Hand *Player::getHand()
{
	return hand;
}

Dice *Player::getDice()
{
	return dice;
}

void Player::addCountry(Country *country)
{
	Player::countries.push_back(country);
}

void Player::removeCountry(Country *country)
{

	this->countries.erase(std::remove(this->countries.begin(), this->countries.end(), country), this->countries.end());
}

vector<Country *> Player::getCountries()
{
	return Player::countries;
}

bool Player::hasCountry(Country *country)
{
	for (int i = 0; i < countries.size(); i++)
	{
		if (countries[i] == country)
			return true;
	}
	return false;
}

bool Player::hasCountry(string name)
{
	for (int i = 0; i < countries.size(); i++)
	{
		if (countries[i]->name == name)
			return true;
	}
	return false;
}

bool Player::reinforce(Country *country, int reinforcement)
{
	if (static_cast<Player *>(country->owner)->name == this->name)
	{
		country->setArmySize(country->getArmySize() + reinforcement);
		return true;
	}
	else
		return false;
}

struct sorter
{
	bool operator()(int i, int j) { return (i < j); }
} sortInt;

bool Player::attack(Country *attackingCountry, Country *defendingCountry)
{
	Player *attacker = static_cast<Player *>(attackingCountry->owner);
	Player *defender = static_cast<Player *>(defendingCountry->owner);
	if (attacker->name == defender->name || attacker->name != this->name || attackingCountry->getArmySize() < 2)
		return false;
	int attackerArmy = attackingCountry->getArmySize();
	int defenderArmy = defendingCountry->getArmySize();
	int attackerDiceCount = 0;
	int defenderDiceCount = 0;

	attackerDiceCount = attackerArmy > 3 ? 3 : attackerArmy - 1;
	defenderDiceCount = defenderArmy > 1 ? 2 : 1;

	vector<int> attackerRolls = attacker->getDice()->roll(attackerDiceCount);
	vector<int> defenderRolls = defender->getDice()->roll(attackerDiceCount);
	std::sort(attackerRolls.begin(), attackerRolls.end(), sortInt);
	std::sort(defenderRolls.begin(), defenderRolls.end(), sortInt);
	for (int i = 0; i < attackerDiceCount; i++)
	{
		if ((i > defenderDiceCount - 1) || (attackerRolls.at(i) > defenderRolls.at(i)))
		{
			defendingCountry->setArmySize(defendingCountry->getArmySize() - 1);
			if (defendingCountry->getArmySize() < 1)
			{
				attackingCountry->setArmySize(attackingCountry->getArmySize() - 1);
				defendingCountry->setArmySize(1);
				defendingCountry->owner = attacker;
				attacker->addCountry(defendingCountry);
				defender->removeCountry(defendingCountry);
			}
		}
		else
			attackingCountry->setArmySize(attackingCountry->getArmySize() - 1);
	}

	return true;
}

void Player::fortify()
{
}