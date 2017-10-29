#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include "player.h"
#include "map.h"

class Game
{
      public:
        Game() {}
        ~Game(){};
        static Game *getInstance();
        void reinforceCountry();
	void attackCountry();
        void fortifyCountry();
        void turn();
        void nextTurn();

      private:
        vector<Player *> players;
        int currentPlayer;
        Map *map = nullptr;
};

#endif