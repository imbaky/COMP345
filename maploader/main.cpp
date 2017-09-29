#include <iostream>
#include <stdlib.h>
#include <limits>
#include "Maploader.h"

using namespace std;

int main()
{
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "                                                                     " << endl;
	cout << " RRRRRRRRRRRRRRRRR     iiii                   kkkkkkkk               " << endl;
	cout << " R::::::::::::::::R   i::::i                  k::::::k               " << endl;
	cout << " R::::::RRRRRR:::::R   iiii                   k::::::k               " << endl;
	cout << " RR:::::R     R:::::R                         k::::::k               " << endl;
	cout << " R::::R     R:::::Riiiiiii     ssssssssss     k:::::k    kkkkkkk      " << endl;
	cout << " R::::R     R:::::Ri:::::i   ss::::::::::s    k:::::k   k:::::k       " << endl;
	cout << " R::::RRRRRR:::::R  i::::i ss:::::::::::::s   k:::::k  k:::::k        " << endl;
	cout << " R:::::::::::::RR   i::::i s::::::ssss:::::s  k:::::k k:::::k         " << endl;
	cout << " R::::RRRRRR:::::R  i::::i  s:::::s  ssssss   k::::::k:::::k          " << endl;
	cout << " R::::R     R:::::R i::::i    s::::::s        k:::::::::::k           " << endl;
	cout << " R::::R     R:::::R i::::i       s::::::s     k:::::::::::k           " << endl;
	cout << " R::::R     R:::::R i::::i   sssss   s:::::s  k::::::k:::::k          " << endl;
	cout << " RR:::::R     R::::Ri::::i  s:::::ssss::::s  k::::::k k:::::k       " << endl;
	cout << " R::::::R     R::::Ri::::i  s::::::::::::::s k::::::k  k:::::k      " << endl;
	cout << " R::::::R     R::::Ri::::i   s:::::::::::ss  k::::::k   k:::::k     " << endl;
	cout << " RRRRRRRR     RRRRRRRiiiiii    sssssssssss    kkkkkkkk    kkkkkkk    " << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;


	cout << "\n\n";
	cout << "Generating new map from World.map ...\n\n";
	
	MapLoader *ml = new MapLoader();
	ml->loadMap("World.map");

	Map *map = ml->getMap();

	vector <Continent *>continents = map->getContinents();

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
