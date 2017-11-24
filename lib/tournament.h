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
	int numberOfMaps;
	int numberOfComputers;
	int numberOfGames;
	int numberOfTurns;
};
	
#endif


