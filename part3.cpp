#include <iostream> // std::cout
#include <vector>   // std::vector
#include <iterator> // std::iterator

#include "./lib/player.h"
#include "./lib/Maploader.h"
#include "./lib/game.h"
#include "utils.h"

bool ownAll();
int main()
{
        cout << "Part 3!\n" << endl;

        displayLogo();
        
        Game* game = game->getInstance();
        
        game->setMap(loadMap());
        game->setPlayers(createPlayers());

        while(!(game->hasWon())){
                game->turn();

                if(!(game->hasWon()))
                        game->nextTurn();
        }

        return 0;
}
