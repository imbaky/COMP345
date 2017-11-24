#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <vector>

#include "game.h"
#include "map.h"

using namespace std;

class Tournament {
public:
	void setup();
	void start();
	int getTurns();
private:
	vector<vector<Game *>> mapGames;
	int turns;
};
	
#endif


