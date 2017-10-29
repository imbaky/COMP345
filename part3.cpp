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
        Map* map=loadMap();
       
        //player 2 owns all the countries
        vector<Player*> players=createPlayers();
        vector<Continent *> continents=map->getContinents();
        for (std::vector<Continent *>::iterator it = continents.begin(); it != continents.end(); ++it)
        {
                vector<Country *> countries= (*it)->getCountries();
                for (std::vector<Country *>::iterator it2 = countries.begin(); it2 != countries.end(); ++it2){
                        players.at(1)->addCountry(*it2);
                }
        }


        game->setMap(map);
        game->setPlayers(players);

        while(!(game->hasWon())){
                game->turn();

                if(!(game->hasWon()))
                        game->nextTurn();
        }

        return 0;
}
