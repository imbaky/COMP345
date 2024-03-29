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
        void createDeck(int countries);
        void createPlayers();
	void createPlayers(int numOfPlayers);
        void start_game();
        int players_number();
        void reinforcementPhase();
        void attackPhase();
        void fortificationPhase();
        void printPlayerInfo(Player *player);
        void displayLogo();
	vector<Player *> get_players();
	int getTurnNumber();
	Map *getMap();
	Deck *getDeck();

	void register_observer(AbstractObserver *observer);
	void notify_current_player();
	void notify_current_phase(string phase);
	void notify_msg(string msg);
	void notify_game_stats();

private:
	int turnNumber = 0;
        vector<Player *> players;
        int currentPlayer = 0;
        Map *map = nullptr;
	Deck *deck;

	vector<AbstractObserver *> observers;
};

#endif
