#ifndef MAP_H
#define MAP_H

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Player;

class Country {
public:
	string name;
	int posX;
	int posY;
	Player *owner;


	Country(string name, int posX, int posY);
	
	vector<Country *> getNeighbors();
	void addNeighbor(Country *country);
	bool hasNeighbor(Country *country);
	bool hasNeighbor(string country);
	bool hasNeighbor();
	// bool isOwner(Player *player);
	bool setArmySize(int army_size);
	int getArmySize();
private:
	vector<Country *> neighbors;
	int army;
	
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
	int countryCount();
private:
	vector<Continent *> continents;
	int country_count;
};

#endif
