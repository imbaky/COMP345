#include <algorithm>
#include <assert.h>
#include <iostream>

#include "card.h"

Deck::Deck()
{
	initialize(DEFAULT_SIZE, DEFAULT_SIZE, DEFAULT_SIZE);
}

Deck::Deck(int countries)
{
	int c = countries / 3;
	initialize(c, c, c);
}

Deck::Deck(int i, int a, int c)
{
	initialize(i, a, c);
}

void Deck::initialize(int infantries, int artilleries, int cavaleries)
{
	for (int i = 0; i < infantries; i++)
		cards.push_back(Infantry);
	for (int i = 0; i < artilleries; i++)
		cards.push_back(Artillery);
	for (int i = 0; i < cavaleries; i++) 
		cards.push_back(Cavalery);
	random_shuffle(cards.begin(), cards.end());
}

Card Deck::draw()
{
	assert(!cards.empty());
	Card card = cards.back();
	cards.pop_back();
	return card;
}

int Deck::size()
{
	return cards.size();
}

bool Deck::empty()
{
	return cards.empty();
}

void Hand::drawCard(Deck *deck)
{
	if (!deck->empty())
		add(deck->draw());
}

int Hand::infantrySize()
{
	return infantries;
}

int Hand::cavalerySize()
{
	return cavaleries;
}

int Hand::artillerySize()
{
	return artilleries;
}

void Hand::add(Card card)
{
	switch (card) {
	case Infantry:
		infantries++;
		break;
	case Cavalery:
		cavaleries++;
		break;
	case Artillery:
		artilleries++;
		break;
	default:
		break;
	}
}

int Hand::exchange()
{
	int armies = 0;
	while (infantrySize() > 0 && cavalerySize() > 0 && artillerySize() > 0) {
		armies += 12;
		infantries--;
		cavaleries--;
		artilleries--;
	}
	return armies;
}

int Hand::exchange(Card card)
{
	int armies = 0;
	switch (card) {
	case Infantry:
		armies = 4 * (infantrySize() / 3);
		infantries -= (infantrySize() / 3) == 0 ?
			infantries : infantries - infantries % 3;
		break;
	case Cavalery:
		armies = 6 * (cavalerySize() / 3);
		cavaleries -= (cavalerySize() / 3) == 0 ?
			cavaleries : cavaleries - cavaleries % 3;
		break;
	case Artillery:
		armies = 8 * (artillerySize() / 3);
		artilleries -= (artillerySize() / 3) == 0 ?
			artilleries : artilleries - artilleries % 3;
		break;
	default:
		break;
	}
	return armies;
}
