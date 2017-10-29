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
        std::cout << "reinforceCountry" << endl;
}
void Game::attackCountry()
{
        std::cout << "attackCountry" << endl;
}
void Game::fortifyCountry()
{
        std::cout << "fortifyCountry" << endl;
}

void Game::turn()
{
        this->fortifyCountry();
        this->attackCountry();
        this->fortifyCountry();
}

void Game::nextTurn()
{
        currentPlayer = (currentPlayer + 1) % players.size();
}