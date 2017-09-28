#include <vector>
#include <string>

#include "../map/map.h"
#include "../dice/dice.h"
#include "../cards/card.h"

using namespace std;

class Player {
public:
	string name;
	Player(string name);
	
	void reinforce();
	void attack();
	void fortify();

	Hand getHand();
	Dice getDice();
	vector<Country *> getCountries();
private:
	Hand *hand;
	Dice *dice;
	vector<Country *> countries;

};
