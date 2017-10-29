#include "game.h"
#include <iostream>

Game *Game::getInstance()
{
        static Game *instance = nullptr;
        if (instance == nullptr)
        {
                instance = new Game();
        }
        return instance;
}

void Game::reinforceCountry()
{
        std::cout << "Reinforce phase" << endl;
}
void Game::attackCountry()
{
        std::cout << "Attack phase" << endl;
}
void Game::fortifyCountry()
{
        std::cout << "Fortify phase" << endl;
}

void Game::turn()
{
        this->reinforceCountry();
        this->attackCountry();
        this->fortifyCountry();
}

void Game::nextTurn()
{
        currentPlayer = (currentPlayer + 1) % players.size();
}

bool Game::setPlayers(vector<Player *> players)
{
        this->players=players;
}

Player* Game::getCurrentPlayer()
{
        return this->players.at(this->currentPlayer);
}

bool Game::setMap(Map *map){
        this->map=map;
}

bool Game::hasWon(){
        if(this->map->countryCount()==this->players.at(this->currentPlayer)->getCountries().size()){
                return true;
        }
        return false;
}

