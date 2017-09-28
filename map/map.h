#ifndef MAP_H
#define MAP_H

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Country {
public:
	string name;
	int posX;
	int posY;
	vector<Country *> neighbors;

	Country(string name, int posX, int posY);
	void addNeighbor(Country *country);
	bool hasNeighbor(Country *country);
	bool hasNeighbor(string country);
};

class Continent {
public:
	string name;
	vector<Country *> countries;

	Continent(string name);
	void addCountry(Country *country);
	bool hasCountry(Country *country);
	bool hasCountry(string country);
};

class Map {
public:
	vector<Continent *> continents;

	void addContinent(Continent *continent);
};

#endif
