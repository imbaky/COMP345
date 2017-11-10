

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

	cout << "DEBUGGING..." << endl;

	//Distribute countries between players
        int num_player = game->get_players().size();
        int index = 0;
	cout << "DEBUGGING..." << num_player << endl;
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

	cout << "DEBUGGING..." << num_player << endl;
	
	int initial_army = 40 - ((num_player - 2) * 5);
        //Distribute a players armies among their countries
	for (int i = 0; i < game->get_players().size(); i++) {
		int army_available = initial_army;
		vector<Country *> countries = game->get_players()[i]->getCountries();

		while (army_available > 0)
                        for (int j = 0; j < countries.size(); j++) {
                                if (army_available-- > 0) {
                                        countries[i]->setArmySize((countries[i]->getArmySize()) + 1);
                                }
                                else
                                        break;
                        }
	}
	
	cout << "DEBUGGING..." << num_player << endl;
	
	game->reinforcementPhase();

	cout << "DEBUGGING..." << num_player << endl;

	game->fortificationPhase();

	cout << "DEBUGGING..." << num_player << endl;

	game->attackPhase();

	cout << "DEBUGGING..." << num_player << endl;
	
	return 0;
}
