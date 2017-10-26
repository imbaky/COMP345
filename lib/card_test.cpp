#include <iostream>

#include "card.h"

int main()
{
	int armies = 0;
	Hand* hand = new Hand();
	Deck* deck = new Deck(18);

	cout << "Initializing 18 country deck..." << "\n";
	cout << "Adding cards to hand..." << "\n";
	while (!deck->empty()) {
		Card card =  deck->draw();
		hand->add(card);
	}

	cout << "Adding even more cards (beyond 18) to hand..." << "\n\n";
	hand->add(Infantry);
	hand->add(Artillery);
	hand->add(Artillery);

	cout << "Infantries: " << hand->infantrySize() << "\n";
	cout << "Cavalery: " << hand->cavalerySize() << "\n";
	cout << "Artillery: " << hand->artillerySize() << "\n\n";

	cout << "Exchanging infantries..." << "\n";
	armies = hand->exchange(Infantry);
	cout << "Army: " << armies << "\n";
	cout << "Infantries: " << hand->infantrySize() << "\n";
	cout << "Cavalery: " << hand->cavalerySize() << "\n";
	cout << "Artillery: " << hand->artillerySize() << "\n\n";

	cout << "Exchanging all kinds..." << "\n";
	armies += hand->exchange();
	cout << "Army: " << armies << "\n";
	cout << "Infantries: " << hand->infantrySize() << "\n";
	cout << "Cavalery: " << hand->cavalerySize() << "\n";
	cout << "Artillery: " << hand->artillerySize() << "\n";

	
	return 0;
}
