

#include "./lib/game.h"
#include "./lib/observer.h"

using namespace std;

int main() {
	Game *game = new Game();

	Observer *obs1 = new Observer();
	game->register_observer(obs1);
	

	game->displayLogo();
	game->start_game();
	
	Map *map = game->loadMap();

	int countriesCount = 0;
	vector<Continent *> continents = map->getContinents();
        for (int i = 0; i < continents.size(); i++) {
                countriesCount += continents[i]->getCountries().size();
        }
	
	Deck *deck = game->createDeck(countriesCount);

	game->createPlayers();

	//Distribute countries between players
        int num_player = game->get_players().size();
        int index = 0;
        for (std::vector<Continent *>::iterator it = continents.begin(); it != continents.end(); ++it)
        {
                vector<Country *> countries = (*it)->getCountries();
                for (std::vector<Country *>::iterator it2 = countries.begin(); it2 != countries.end(); ++it2)
                {
                        game->get_players().at(index)->addCountry((*it2));
                        (*it2)->owner = (game->get_players().at(index));
                        index = (index + 1) % num_player;
                }
        }

	int initial_army = 40 - ((num_player - 2) * 5);
        //Distribute a players armies among their countries
        for (std::vector<Player *>::iterator it = game->get_players().begin(); it != game->get_players().end(); ++it)
        {
                int army_available = initial_army;
                vector<Country *> countries = (*it)->getCountries();
                while (army_available > 0)
                        for (std::vector<Country *>::iterator it2 = countries.begin(); it2 != countries.end(); ++it2)
                        {
                                if (army_available-- > 0)
                                {
                                        (*it2)->setArmySize(((*it2)->getArmySize()) + 1);
                                }
                                else
                                        break;
                        }
        }

	game->reinforcementPhase();

	game->fortificationPhase();

	game->attackPhase();
	
	return 0;
}
