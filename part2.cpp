#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <random>       // std::

#include "./lib/player.h"
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

    cout<<"Print players in order of their turns :"<<endl;
    for (std::vector<Player*>::iterator it=players.begin(); it!=players.end(); ++it)
    std::cout << ' ' << (*it)->name << endl;
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