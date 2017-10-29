#include <iostream> // std::cout
#include <vector>   // std::vector
#include <iterator> // std::iterator

#include "./lib/player.h"
#include "./lib/Maploader.h"
#include "./lib/game.h"
#include "./utils.h"

void playerOwnsAll(Player* player, Map* map);
int main()
{
        cout << "Part 3!\n" << endl;

        displayLogo();
        


        Game* game = game->getInstance();
        Map* map=loadMap();
        game->setMap(map);
        game->setPlayers(createPlayers());

        while(!(game->hasWon())){
                game->turn();
                playerOwnsAll(game->getCurrentPlayer(),map);
                if(!(game->hasWon()))
                        game->nextTurn();
                        else 
                        std::cout << "Congratulations "<< game->getCurrentPlayer()->name << " you won the game !!" <<endl;
        }

        return 0;
}
void playerOwnsAll(Player* player, Map* map){
        char input;
        
		cout<<"Did "<< player->name <<" aquire all the countries? (y)"<<endl;
		cin>>input;
		if(input=='y'){
                        vector<Continent *> continents=map->getContinents();
                        for (std::vector<Continent *>::iterator it = continents.begin(); it != continents.end(); ++it)
                        {
                                vector<Country *> countries= (*it)->getCountries();
                                for (std::vector<Country *>::iterator it2 = countries.begin(); it2 != countries.end(); ++it2){
                                        player->addCountry(*it2);
                                }
                        }
		}
	
        
}