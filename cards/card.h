#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>

#define DEFAULT_SIZE 10
#define card_type(i) CARD_TYPE[i]

using namespace std;

const string CARD_TYPE[] = { "Infantry", "Cavalery", "Artillery" };

enum Card { Infantry, Cavalery, Artillery };

class Deck {
public:
	Deck();
	Deck(int countries);
	Deck(int infantries, int cavaleries, int artilleries);
	Card draw();
	bool empty();
	int size();
private:
	vector<Card> cards;
	void initialize(int infantries, int cavaleries, int artilleries);
};

class Hand {
public:
	int exchange();
	int exchange(Card card);
	void add(Card card);
	void drawCard(Deck *deck);
	int infantrySize();
	int cavalerySize();
	int artillerySize();
private:
	int infantries;
	int cavaleries;
	int artilleries;
};

#endif
