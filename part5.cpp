#include "./utils.h"
#include "./lib/player.h"
#include "./lib/card.h"

#define ARRAY_SIZE(array) (sizeof((array)) / sizeof((array[0])))

using namespace std;

int main()
{
        displayLogo();
        start_game();

        Map *map = loadMap();

        int countriesCount = 0;
        vector<Continent *> continents = map->getContinents();
        for (int i = 0; i < continents.size(); i++)
        {
                countriesCount += continents[i]->getCountries().size();
        }

        Deck *deck = createDeck(countriesCount);

        vector<Player *> players = createPlayers();

        cout << "\n\n===\nMAP:\n===\n";
        for (int i = 0; i < continents.size(); i++)
        {
                cout << "CONTINENT: " << continents[i]->name << "\n------------------------\n";
                vector<Country *> countries = continents[i]->getCountries();
                for (int j = 0; j < countries.size(); j++)
                {
                        cout << countries[j]->name << ": ";
                        vector<Country *> neighbors = countries[j]->getNeighbors();
                        for (int k = 0; k < neighbors.size(); k++)
                        {
                                cout << neighbors[k]->name << ", ";
                        }
                        cout << "\n";
                }
                cout << "\n";
        }

        //Distribute countries between players
        int num_player = players.size();
        int index = 0;
        for (std::vector<Continent *>::iterator it = continents.begin(); it != continents.end(); ++it)
        {
                vector<Country *> countries = (*it)->getCountries();
                for (std::vector<Country *>::iterator it2 = countries.begin(); it2 != countries.end(); ++it2)
                {
                        players.at(index)->addCountry((*it2));
                        (*it2)->owner = (players.at(index));
                        index = (index + 1) % num_player;
                }
        }
        //number of armies
        int initial_army = 40 - ((num_player - 2) * 5);
        //Distribute a players armies among their countries
        for (std::vector<Player *>::iterator it = players.begin(); it != players.end(); ++it)
        {
                int army_available = initial_army;
                vector<Country *> countries = (*it)->getCountries();
                while (army_available > 0)
                        for (std::vector<Country *>::iterator it2 = countries.begin(); it2 != countries.end(); ++it2)
                        {
                                if (army_available-- > 0)
                                {
                                        //cout<<(static_cast<Player*>((*it2)->owner)->name)<<endl;
                                        (*it2)->setArmySize(((*it2)->getArmySize()) + 1);
                                }
                                else
                                        break;
                        }
        }
        cout << "\n Number of armies per player: " << initial_army << endl;

        cout << "\n\n=======\nPLAYERS:\n=======\n";
        for (int i = 0; i < players.size(); i++)
        {
                printPlayerInfo(players[i]);
        }


        return 0;
}
