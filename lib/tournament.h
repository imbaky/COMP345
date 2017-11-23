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

private:
	vector<Map *> maps;
	vector<Game *> games;
	vector<Deck *> decks;
};
	
#endif
