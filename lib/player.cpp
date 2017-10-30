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

bool Player::attack(Country *attackingCountry, Country *defendingCountry, int attackerDiceCount, int defenderDiceCount)
{
	Player *attacker = static_cast<Player *>(attackingCountry->owner);
	Player *defender = static_cast<Player *>(defendingCountry->owner);
	if (attacker->name == defender->name || attacker->name != this->name || (attackingCountry->getArmySize() < 2) || (attackerDiceCount > 3) || (attackerDiceCount > attackingCountry->getArmySize()) || (defenderDiceCount > 2) || (defenderDiceCount > attackingCountry->getArmySize()))
		return false;

	// int attackerArmy = attackingCountry->getArmySize();
	// int defenderArmy = defendingCountry->getArmySize();
	// int attackerDiceCount = 0;
	// int defenderDiceCount = 0;

	// attackerDiceCount = attackerArmy > 3 ? 3 : attackerArmy - 1;
	// defenderDiceCount = defenderArmy > 1 ? 2 : 1;

	vector<int> attackerRolls = attacker->getDice()->roll(attackerDiceCount);
	vector<int> defenderRolls = defender->getDice()->roll(attackerDiceCount);
	std::sort(attackerRolls.begin(), attackerRolls.end(), sortInt);
	std::sort(defenderRolls.begin(), defenderRolls.end(), sortInt);
	cout << attackingCountry->name << " is owned by " << static_cast<Player *>(attackingCountry->owner)->name << " and has an army of " << attackingCountry->getArmySize() << endl;
	cout << defendingCountry->name << " is owned by " << static_cast<Player *>(defendingCountry->owner)->name << " and has an army of " << defendingCountry->getArmySize() << endl;
	cout << attackingCountry->name << " is attacks " << defendingCountry->name << endl;
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

		if (attackingCountry->getArmySize() == 1)
			break;
	}
	cout << attackingCountry->name << " is owned by " << static_cast<Player *>(attackingCountry->owner)->name << " and has an army of " << attackingCountry->getArmySize() << endl;
	cout << defendingCountry->name << " is owned by " << static_cast<Player *>(defendingCountry->owner)->name << " and has an army of " << defendingCountry->getArmySize() << endl;
	return true;
}

bool Player::fortify(Country *source, Country *target, int fortificationAmount)
{
	if ((static_cast<Player *>(source->owner)->name != static_cast<Player *>(target->owner)->name) || (target->getArmySize() - fortificationAmount) < 2)
		return false;
	else
	{
		source->setArmySize(source->getArmySize() - fortificationAmount);
		target->setArmySize(target->getArmySize() + fortificationAmount);
	}
}