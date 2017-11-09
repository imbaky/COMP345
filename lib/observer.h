#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>


using namespace std;


class Game;

class Observer
{
public:
	Observer(Game game);
	
	void notify(string msg);
};

#endif
