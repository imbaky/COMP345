#include "map.h"

Country::Country(string countryName, int x, int y) : name(countryName), posX(x), posY(y), army(0)
{
}

vector<Country *> Country::getNeighbors()
{
	return neighbors;
}

void Country::addNeighbor(Country *country)
{
	if (!hasNeighbor(country))
	{
		neighbors.push_back(country);
		country->addNeighbor(this);
	}
}

bool Country::isOwner(Player *player){
	return static_cast<Player *>(this->owner)->name == static_cast<Player *>(player->owner)->name;	
}

bool Country::hasNeighbor(Country *country)
{
	vector<Country *> neighbors = getNeighbors();
	for (int i = 0; i < neighbors.size(); i++)
	{
		if (neighbors[i] == country)
			return true;
	}
	return false;
}

bool Country::hasNeighbor(string country)
{
	vector<Country *> neighbors = getNeighbors();
	for (int i = 0; i < neighbors.size(); i++)
	{
		if (neighbors[i]->name == country)
			return true;
	}
	return false;
}

bool Country::hasNeighbor()
{
	return neighbors.size() == 0;
}

Continent::Continent(string continentName) : name(continentName) {}

vector<Country *> Continent::getCountries()
{
	return countries;
}

void Continent::addCountry(Country *country)
{
	if (!hasCountry(country))
	{
		countries.push_back(country);
	}
}

bool Continent::hasCountry(Country *country)
{
	vector<Country *> countries = getCountries();
	for (int i = 0; i < countries.size(); i++)
	{
		if (countries[i] == country)
			return true;
	}
	return false;
}
bool Continent::hasCountry(string country)
{
	vector<Country *> countries = getCountries();
	for (int i = 0; i < countries.size(); i++)
	{
		if (countries[i]->name == country)
			return true;
	}
	return false;
}

vector<Continent *> Continent::getNeighbors()
{
	return neighbors;
}

void Continent::addNeighbor(Continent *continent)
{
	if (!hasNeighbor(continent))
	{
		neighbors.push_back(continent);
		continent->addNeighbor(this);
	}
}

bool Continent::hasNeighbor(Continent *continent)
{
	vector<Continent *> neighbors = getNeighbors();
	for (int i = 0; i < neighbors.size(); i++)
	{
		if (neighbors[i] == continent)
			return true;
	}
	return false;
}
bool Continent::hasNeighbor(string continent)
{
	vector<Continent *> neighbors = getNeighbors();
	for (int i = 0; i < neighbors.size(); i++)
	{
		if (neighbors[i]->name == continent)
			return true;
	}
	return false;
}

vector<Continent *> Map::getContinents()
{
	return continents;
}

void Map::addContinent(Continent *continent)
{
	if (!hasContinent(continent))
	{
		continents.push_back(continent);
	}
}

bool Map::hasContinent(Continent *continent)
{
	vector<Continent *> continents = getContinents();
	for (int i = 0; i < continents.size(); i++)
	{
		if (continents[i] == continent)
			return true;
	}
	return false;
}

bool Map::hasContinent(string continent)
{
	vector<Continent *> continents = getContinents();
	for (int i = 0; i < continents.size(); i++)
	{
		if (continents[i]->name == continent)
			return true;
	}
	return false;
}

int Map::countryCount(){
	if(this->country_count==0)
	for (std::vector<Continent *>::iterator it = continents.begin(); it != continents.end(); ++it)
        {
                vector<Country *> countries = (*it)->getCountries();
                for (std::vector<Country *>::iterator it2 = countries.begin(); it2 != countries.end(); ++it2)
                {
			this->country_count++;
                }
        }
	return this->country_count;
}

bool Country::setArmySize(int army_size)
{
	army = army_size;
	return true;
}

int Country::getArmySize()
{
	return army;
}

