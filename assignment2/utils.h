#ifndef UTILS_H
#define UTILS_H

#include <string.h>

#include "./lib/Maploader.h"
#include "./lib/player.h"
#include "./lib/card.h"


void start_game();
string select_map();
int players_number();

Map *loadMap();
Deck *createDeck(int countries);
vector<Player *> createPlayers();

void reinforcementPhase(Player *player, Map *map);
void attackPhase(Player *player);
void fortificationPhase(Player *player);

int numOfContinents(Player *player, Map *map);

void printPlayerInfo(Player *player);

void displayLogo();
	
#endif
