

#include "./lib/game.h"
#include "./lib/observer.h"
#include "./lib/tournament.h"


#include "./lib/dice.h"
#include "./lib/die.h"


using namespace std;

int main() {
	Tournament *tourney = new Tournament();

	tourney->start();

	return 0;
}
