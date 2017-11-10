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
	if ((static_cast<Player *>(source->owner)->name != static_cast<Player *>(target->owner)->name) || (target->getArmySize() - fortificationAmount) < 1)
		return false;
	else
	{
		source->setArmySize(source->getArmySize() - fortificationAmount);
		target->setArmySize(target->getArmySize() + fortificationAmount);
		return true;
	}
}

int Player::numOfContinents(Map *map)
{
	Player *player=this;
	
	int owned = 0;
	vector<Continent *> continents = map->getContinents();
	vector<Country *> countries = player->getCountries();

	for (int i = 0; i < continents.size(); i++)
	{
		vector<Country *> continentCountries = continents[i]->getCountries();
		for (int j = 0; j < continentCountries.size(); j++)
		{
			vector<Country *>::iterator it = find(countries.begin(), countries.end(), continentCountries[j]);
			if (it == countries.end())
			{
				break;
			}
			if (j == continentCountries.size() - 1)
			{
				owned++;
			}
		}
	}

	return owned;
}

bool Human::attack(){

char input;
		bool validInput = false;
		// A player's countries
		vector<Country *> countries = this->getCountries();

		cout << "Select a country that you would like to attack from:" << endl;
		for (int i = 0; i < this->getCountries().size(); i++)
		{
			cout << i << "- " << this->getCountries().at(i)->name << " Army size:" << this->getCountries().at(i)->getArmySize() << endl;
		}

		while (!validInput)
		{
			cout << "Attack? (y/n)\n";
			cin >> input;
			if (input == 'y')
			{

				int attackCountry;
				cin >> attackCountry;

				vector<Country *> neighbors;
				for (int i = 0; i < this->getCountries().at(attackCountry)->getNeighbors().size(); i++)
				{
					if (static_cast<Player *>(this->getCountries().at(attackCountry)->getNeighbors().at(i)->owner)->name != static_cast<Player *>(this->getCountries().at(attackCountry)->owner)->name)
						neighbors.push_back(this->getCountries().at(attackCountry)->getNeighbors().at(i));
				}

				cout << "Select a neighboring country that you would like to attack:" << endl;
				for (int i = 0; i < neighbors.size(); i++)
				{
					cout << i << "- " << neighbors.at(i)->name << " Army size:" << neighbors.at(i)->getArmySize() << endl;
				}
				int enemyCountry;
				cin >> enemyCountry;

				int attackerDices, defenderDices;

				cout << static_cast<Player *>(this->getCountries().at(attackCountry)->owner)->name << " Number of dices to attack (1, 2 or 3)?" << endl;
				cin >> attackerDices;

				cout << static_cast<Player *>(neighbors.at(enemyCountry)->owner)->name << " Number of dices to defend (1 or 2)?" << endl;
				cin >> defenderDices;
				// notify_msg("Attacking from" + this->getCountries().at(attackCountry)->name + " to " + this->getCountries().at(attackCountry)->name);
				if (Player::attack(this->getCountries().at(attackCountry), neighbors.at(enemyCountry), attackerDices, defenderDices))
					cout << "Attack successful!!" << endl;
				else
				{
					validInput = false;
					cout << "invalid input";
				}
			}
			if (input == 'n')
				validInput = true;
		}
return true;
}

bool attack(){

	
}