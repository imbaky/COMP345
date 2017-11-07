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
        vector<Player *> Game::createPlayers();
        void Game::start_game();
        int Game::players_number();
        void Game::reinforcementPhase(Player *player, Map *map);
        void Game::attackPhase(Player *player);
        void Game::fortificationPhase(Player *player);
        int Game::numOfContinents(Player *player, Map *map);
        void Game::printPlayerInfo(Player *player);
        void Game::displayLogo();

      private:
        vector<Player *> players;
        int currentPlayer;
        Map *map = nullptr;
};

#endif