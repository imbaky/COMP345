#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <random>       // std::

#include "./lib/player.h"
#include "./lib/Maploader.h"
#include "utils.h"
#include <iterator>




int main()
{
    cout<<"Part 2!\n"<<endl;
    
    displayLogo();

    int num_player=players_number();
    vector<Player*> players;
    for(int i=0;i<num_player;i++){
        players.push_back(new Player("Player "+to_string(i+1), 3));
    }

    /*  shuffle players order
    *  Reference: https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector
    */
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(players), std::end(players), rng);
    


    //number of armies
    int initial_army=40-((num_player-2)*5);
    

    //Distribute countries between players
    MapLoader *ml = new MapLoader();
	ml->loadMap("./maps/World.map");
    Map *map = ml->getMap();
    vector <Continent *>continents = map->getContinents();
    int index=0;
    for (std::vector<Continent *>::iterator it=continents.begin(); it!=continents.end(); ++it){
        vector <Country *>countries=(*it)->getCountries();
        for (std::vector<Country *>::iterator it2=countries.begin(); it2!=countries.end(); ++it2){
        players.at(index)->addCountry((*it2));
        index=(index+1)%num_player;
        }
    }


    
    //Distribute a players armies among their countries
    for (std::vector<Player*>::iterator it=players.begin(); it!=players.end(); ++it){
        int army_available=initial_army;
        vector <Country *>countries=(*it)->getCountries();
        while(army_available>0)
        for (std::vector<Country *>::iterator it2=countries.begin(); it2!=countries.end(); ++it2){
                if(army_available-->0){
                        (*it2)->setArmySize(((*it2)->getArmySize())+1);
                }else break;
        }
    }
            cout<< "\n Number of armies per player: " << initial_army <<endl;

            // Prints players in order with the number of countries
            cout<<"\n\n Print players in order of their turns :\n"<<endl;
            for (std::vector<Player*>::iterator it=players.begin(); it!=players.end(); ++it){
                std::cout<<"-------------------------------------------"<<endl;
                std::cout << ' ' << (*it)->name << " has " << (*it)->getCountries().size() << " countries" << endl;
                std::cout<<"-------------------------------------------"<<endl;
            vector <Country *>countries=(*it)->getCountries();
                for (std::vector<Country *>::iterator it2=countries.begin(); it2!=countries.end(); ++it2){
                    std::cout << ' ' << (*it2)->name << ": army size of " << (*it2)->getArmySize() <<endl;
                }
                
            }
            
            

    return 0;
}
