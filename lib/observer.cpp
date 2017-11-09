
#include <string>

#include "observer.h"
#include "game.h"

using namespace std;


Observer::Observer() {}

void Observer::notify(string msg) {
	cout << "Msg from observable => " << msg << endl;
}
