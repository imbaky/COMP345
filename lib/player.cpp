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

void Player::addCountry(Country* country)
{
	Player::countries.push_back(country);
}

vector<Country *> Player::getCountries()
{
	return Player::countries;
}

bool Player::hasCountry(Country* country)
{
	for (int i = 0; i < countries.size(); i++) {
		if (countries[i] == country)
			return true;
	}
	return false;
}


bool Player::hasCountry(string name)
{
	for (int i = 0; i < countries.size(); i++) {
		if (countries[i]->name == name)
			return true;
	}
	return false;
}


bool Player::reinforce(Country* country, int reinforcement){
	if(static_cast<Player*>(country->owner)->name==this->name){
		country->setArmySize(country->getArmySize()+reinforcement);
		return true;
	}
	else return false;

}

void Player::attack(){

}

void Player::fortify(){


}