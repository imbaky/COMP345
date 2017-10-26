#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <random>       // std::

#include "./lib/player.h"
#include "./lib/Maploader.h"
#include <iterator>



// function declaration
int players_number();

int main()
{
    cout<<"Part 2!\n"<<endl;
    
    cout << "██████╗ ██╗███████╗██╗  ██╗\n"<<
            "██╔══██╗██║██╔════╝██║ ██╔╝\n"<<
            "██████╔╝██║███████╗█████╔╝ \n"<<
            "██╔══██╗██║╚════██║██╔═██╗ \n"<<
            "██║  ██║██║███████║██║  ██╗\n"<<
            "╚═╝  ╚═╝╚═╝╚══════╝╚═╝  ╚═╝\n\n" << endl;
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

        // Prints players in order
        cout<<"Print players in order of their turns :"<<endl;
        for (std::vector<Player*>::iterator it=players.begin(); it!=players.end(); ++it){
        std::cout << ' ' << (*it)->name << " has " << (*it)->getCountries().size() << "countries" << endl;
        vector <Country *>countries=(*it)->getCountries();
            for (std::vector<Country *>::iterator it2=countries.begin(); it2!=countries.end(); ++it2){
                std::cout << ' ' << (*it2)->name <<endl;
            }
        }
        
        cout<< "Number of armies per player: " << initial_army <<endl;
    
    //Distribute a players armies among their countries
    for (std::vector<Player*>::iterator it=players.begin(); it!=players.end(); ++it){
        int army_available=initial_army;
        vector <Country *>countries=(*it)->getCountries();
        while(army_available>0)
        for (std::vector<Country *>::iterator it2=countries.begin(); it2!=countries.end(); ++it2){
                if(army_available-->0){
                        (*it2)->setArmySize(((*it2)->getArmySize())+1);
                        cout<<(*it2)->name<<" has an army of size :"<<(*it2)->getArmySize()<<endl;
                }else break;
        }
    }
    
    return 0;
}

int players_number(){
    bool valid_input=false;
    int input;
    while(!valid_input){
        cout<<"Select the number of players in the game (2-6 players)"<<endl;
        cin>>input;
        if((input>=2)&&(input<=6)){
            valid_input=true;
        }else 
            cerr<<"invalid input !!"<<endl;
    }
    return input;
}