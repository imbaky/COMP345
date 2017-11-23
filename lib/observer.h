#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>
#include <vector>


using namespace std;


class Game;
class Player;


class AbstractObserver
{
public:
	virtual void notify(string msg) {};
	virtual void print_game_stats(vector<Player *> players) {};
 	virtual void info(Game *game) {};
};


class Observer: public AbstractObserver
{
public:
	Observer();
	
	void notify(string msg);

	void print_game_stats(vector<Player *> playersx);

	void info(Game *game);
};


class ObserverDecorator: public AbstractObserver
{
public:
	ObserverDecorator(AbstractObserver *obs);
	void notify(string msg);
	void print_game_stats(vector<Player *> players);
	void info(Game *game); // Delegate to Decorator implementations
	
private:
	AbstractObserver *wrapped_obs;
};


class PlayerDominationObserver: public ObserverDecorator
{
public:
	PlayerDominationObserver(AbstractObserver *obs);
	
	void info(Game *game);
};

class PlayerHandObserver: public ObserverDecorator
{
public:
	PlayerHandObserver(AbstractObserver *obs);
	
	void info(Game *game);
};

class ContinentControlObserver: public ObserverDecorator
{
public:
	ContinentControlObserver(AbstractObserver *obs);
	
	void info(Game *game);
};

#endif
