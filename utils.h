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

void reinforcementPhase(Player *player);
void attackPhase(Player *player);
void fortificationPhase(Player *player);
void displayLogo();
#endif
