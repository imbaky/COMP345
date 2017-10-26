#include "player.h"

Player::Player(string playerName, int numberOfDices)
{
	name = playerName;
	hand = new Hand();
	dice = new Dice(numberOfDices);
}

int Player::getArmies() {
	return armies;
}

void Player::setArmies(int newArmies) {
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

void Player::addCountry(Country* country){
Player::countries.push_back(country);
}

vector<Country *> Player::getCountries(){
	return Player::countries;
	}
