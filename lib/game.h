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
        
        void reinforcePhase();
	      void attackPhase();
        void fortifyPhase();

        void turn();
        void nextTurn();
        bool setPlayers(vector<Player *> players);
        bool setMap(Map *map);
        bool hasWon();
        Player* getCurrentPlayer();
      private:
        vector<Player *> players;
        int currentPlayer;
        Map *map = nullptr;
};

#endif