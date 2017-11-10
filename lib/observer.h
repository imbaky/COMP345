#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>
#include <vector>


using namespace std;


class Game;
class Player;

class Observer
{
public:
	Observer();
	
	void notify(string msg);

	void print_game_stats(vector<Player *> players);
};

#endif
