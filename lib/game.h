#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include "player.h"
#include "map.h"
#include "observer.h"


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
        void printPlayerInfo(Player *player);
        void displayLogo();

	void registerObserver(Observer *observer);
	void notify_current_player();
	void notify_current_phase(string phase);

private:
        vector<Player *> players;
        int currentPlayer;
        Map *map = nullptr;

	vector<Observer *> observers;
};

#endif
