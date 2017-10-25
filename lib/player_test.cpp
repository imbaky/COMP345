#include <iostream>

#include "player.h"
#include "card.h"
#include "dice.h"

int main()
{
	// Game deck
	cout << "Initializing 90 card deck" << "\n";
	Deck *deck = new Deck(90);

	Player *player1 = new Player("Alice", 3);
	Player *player2 = new Player("Bob", 3);

	cout << "\nPlayer 1 rolling 1 dice...  : " << player1->getDice()->roll(1)
	     << "\n";
	cout << "Player 1 rolling 2 dice...  : " << player1->getDice()->roll(2)
	     << "\n";
	cout << "Player 1 rolling 3 dice...  : " << player1->getDice()->roll(3)
	     << "\n";
	cout << "\nPlayer 2 rolling 1 dice...  : " << player2->getDice()->roll(1)
	     << "\n";
	cout << "Player 2 rolling 2 dice...  : " << player2->getDice()->roll(2)
	     << "\n";
	cout << "Player 2 rolling 3 dice...  : " << player2->getDice()->roll(3)
	     << "\n";

	cout << "\nPlayer 1 drawing 6 card from deck..." << "\n";
	player1->getHand()->drawCard(deck);
	player1->getHand()->drawCard(deck);
	player1->getHand()->drawCard(deck);
	player1->getHand()->drawCard(deck);
	player1->getHand()->drawCard(deck);
	player1->getHand()->drawCard(deck);
	cout << "Player 1's hand: "
	     << player1->getHand()->infantrySize() << " Infantries, "
	     << player1->getHand()->cavalerySize() << " Cavaleries, "
	     << player1->getHand()->artillerySize() << " Artilleries\n";

	cout << "\nPlayer 2 drawing 3 card from deck..." << "\n";
	player2->getHand()->drawCard(deck);
	player2->getHand()->drawCard(deck);
	player2->getHand()->drawCard(deck);
	cout << "Player 2's hand: "
	     << player2->getHand()->infantrySize() << " Infantries, "
	     << player2->getHand()->cavalerySize() << " Cavaleries, "
	     << player2->getHand()->artillerySize() << " Artilleries\n";

	cout << "\n" << deck->size() << " cards remaining in deck.";
}
