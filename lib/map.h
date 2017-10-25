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

	Country(string name, int posX, int posY);
	
	vector<Country *> getNeighbors();
	void addNeighbor(Country *country);
	bool hasNeighbor(Country *country);
	bool hasNeighbor(string country);
private:
	vector<Country *> neighbors;
};

class Continent {
public:
	string name;

	Continent(string name);

	vector<Country *> getCountries();
	vector<Continent *> getNeighbors();
	void addCountry(Country *country);
	bool hasCountry(Country *country);
	bool hasCountry(string country);
	void addNeighbor(Continent *continent);
	bool hasNeighbor(Continent *continent);
	bool hasNeighbor(string continent);
private:
	vector<Country *> countries;
	vector<Continent *> neighbors;
};

class Map {
public:
	vector<Continent *> getContinents();
	void addContinent(Continent *continent);
	bool hasContinent(Continent *continent);
	bool hasContinent(string continent);
private:
	vector<Continent *> continents;
};

#endif
