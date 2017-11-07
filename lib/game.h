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

        void turn();
        void nextTurn();
        bool setPlayers(vector<Player *> players);
        bool setMap(Map *map);
        bool hasWon();
        Player* getCurrentPlayer();
        Map *loadMap();
        string select_map();
        Deck* createDeck(int countries);
        void createPlayers();
        void start_game();
        int players_number();
        void reinforcementPhase();
        void attackPhase();
        void fortificationPhase();
        int numOfContinents(Player *player, Map *map);
        void printPlayerInfo(Player *player);
        void displayLogo();

      private:
        vector<Player *> players;
        int currentPlayer;
        Map *map = nullptr;
};

#endif
