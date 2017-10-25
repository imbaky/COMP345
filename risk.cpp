#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include<string.h>
#include<fstream>
#include<dirent.h>
#include <vector>
#include "./lib/Maploader.h"



using namespace std;

// function declaration
void start_game();
string select_map();
int select_player_number();

int main()
{

    cout<<"Lets play !\n"<<endl;

    cout << "██████╗ ██╗███████╗██╗  ██╗\n"<<
            "██╔══██╗██║██╔════╝██║ ██╔╝\n"<<
            "██████╔╝██║███████╗█████╔╝ \n"<<
            "██╔══██╗██║╚════██║██╔═██╗ \n"<<
            "██║  ██║██║███████║██║  ██╗\n"<<
            "╚═╝  ╚═╝╚═╝╚══════╝╚═╝  ╚═╝\n\n" << endl;
    start_game();
    MapLoader *ml = new MapLoader();
	ml->loadMap(select_map());
    Map *map = ml->getMap();

    vector <Continent *>continents = map->getContinents();
    cout<<continents.size()<<endl;
        for (int i = 0; i < continents.size(); i++) {
            cout << "CONTINENT: " << continents[i]->name << "\n========================\n";
            vector<Country *> countries = continents[i]->getCountries();
            for (int j = 0; j < countries.size(); j++) {
                cout << countries[j]->name << ": ";
                vector<Country *> neighbors = countries[j]->getNeighbors();
                for (int k = 0; k < neighbors.size(); k++) {
                    cout << neighbors[k]->name << ", ";
                }
                cout << "\n";
            }
            cout << "\n";
        }

return 0;

}

void start_game(){
    bool valid_input=false;
    char input;
    while(!valid_input){
        cout<<"Would you like to start the game? (y/n)"<<endl;
        cin>>input;
        if(input=='y'){
            valid_input=true;
        }else if(input!='n')
                cerr<<"invalid input !!"<<endl;
    }
}

string select_map(){
    bool valid_input=false;
    int input;

    DIR *pDIR;
    struct dirent *entry;
    int count=0;
    vector<string> files;
    
    cout<<"\n\n***Available maps***"<< endl;
    if( pDIR=opendir("./maps/") ){
            while(entry = readdir(pDIR)){
                    if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 && entry->d_name[strlen(entry->d_name)-2] == 'a' ){
                        files.push_back(entry->d_name);
                        cout << ++count << "- " <<entry->d_name << "\n";
                    }
            }
            closedir(pDIR);
    }
    while(!valid_input){
        cout<<"Which map would you like to use? (enter number)"<<endl;
        cin>>input;
        if((input>=0)&&(input<=count)){
            valid_input=true;
        }else  cerr<<"invalid input !!"<<endl;
               
    }
    return "./maps/"+files.at(input-1);
}
