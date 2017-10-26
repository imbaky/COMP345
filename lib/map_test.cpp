#include <iostream>

#include "map.h"

int main()
{
	// Map has continents
	// Continents have countries
	// Continents have neighbor continents
	// Countries have neighbor countries
	
	// Map
	Map *map = new Map();

	// Continents
	Continent *na = new Continent("NorthAmerica");
	Continent *asia = new Continent("Asia");

	// Add continents to map
	map->addContinent(na);
	map->addContinent(asia);

	// Countries
	Country *canada = new Country("Canada", 1, 2);
	Country *us = new Country("US", 2, 2);
	Country *russia = new Country("Russia", 3, 3);
	Country *china = new Country("China", 4, 4);

	// Add countries to continents
	na->addCountry(canada);
	na->addCountry(us);
	asia->addCountry(russia);
	asia->addCountry(china);

	// Link Canada to US
	canada->addNeighbor(us);
	// Link US To russia
	us->addNeighbor(russia);
	// Link Russia to China
	russia->addNeighbor(china);

	// Link asia to north america
	na->addNeighbor(asia);

	cout << "\n";
	cout <<"CANADA HAS US NEIGHBOR?: " << canada->hasNeighbor(us) << "\n";
	cout <<"CANADA HAS US NEIGHBOR?: " << canada->hasNeighbor("US") << "\n";
	cout <<"US HAS CANADA NEIGHBOR?: " << us->hasNeighbor(us) << "\n";
	cout <<"US HAS CANADA NEIGHBOR?: " << us->hasNeighbor("Canada") << "\n";

	cout <<"CANADA HAS RUSSIA NEIGHBOR?: " << canada->hasNeighbor(russia) << "\n";
	cout <<"CANADA HAS RUSSIA NEIGHBOR?: " << canada->hasNeighbor("Russia") << "\n";
	
	cout <<"US HAS RUSSIA NEIGHBOR?: " << us->hasNeighbor(russia) << "\n";
	cout <<"US HAS RUSSIA NEIGHBOR?: " << us->hasNeighbor("Russia") << "\n";
	cout <<"RUSSIA HAS US NEIGHBOR?: " << russia->hasNeighbor(us) << "\n";
	cout <<"RUSSIA HAS US NEIGHBOR?: " << russia->hasNeighbor("US") << "\n";
	
	cout <<"RUSSIA HAS CHINA NEIGHBOR?: " << russia->hasNeighbor(china) << "\n";
	cout <<"RUSSIA HAS CHINA NEIGHBOR?: " << russia->hasNeighbor("China") << "\n";

	cout <<"US HAS CHINA NEIGHBOR?: " << us->hasNeighbor(china) << "\n";
	cout <<"US HAS CHINA NEIGHBOR?: " << us->hasNeighbor("China") << "\n";

	cout << "\n";
	cout <<"North America has the following countries:\n";
	for (int i = 0; i < na->getCountries().size(); i++) {
		cout << na->getCountries()[i]->name << "\n";
	}

	cout << "\n";
	cout <<"Asia has the following countries:\n";
	for (int i = 0; i < asia->getCountries().size(); i++) {
		cout << asia->getCountries()[i]->name << "\n";
	}

	cout << "\n";
	cout <<"Asia has the following neighbor continents:\n";
	for (int i = 0; i < asia->getNeighbors().size(); i++) {
		cout << asia->getNeighbors()[i]->name << "\n";
	}

	cout << "\n";
	cout <<"North america has the following neighbor continents:\n";
	for (int i = 0; i < na->getNeighbors().size(); i++) {
		cout << na->getNeighbors()[i]->name << "\n";
	}

	cout << "\n";
	cout <<"The map has the following continents:\n";
	for (int i = 0; i < map->getContinents().size(); i++) {
		cout << map->getContinents()[i]->name << "\n";
	}

	return 0;
}
