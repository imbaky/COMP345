#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <map>

#include "Maploader.h"
#include "map.h"

using namespace std;

const int MAXLINE=256;


template<typename Out>
void split(const std::string &s, char delim, Out result)
{
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

MapLoader::MapLoader()
{
	map = new Map();
}

Map *MapLoader::getMap()
{
	return map;
}

void MapLoader::loadMap(string filename)
{
	std::map<string, Continent *> continents;
	std::map<string, Country *> countries;
	std::map<string, vector<string> > neighbors;
	
	ifstream inFile (filename.c_str());
	string line;
	string current;

	while (getline(inFile, line)) {
		if (line == "[Map]") {
			current = "MAP";
		} else if (line == "[Continents]") {
			current = "CONTINENT";
		} else if (line == "[Territories]") {
			current = "TERRITORIES";
		} else if (current == "MAP") {
			if (line == "")
				continue;
		} else if (current == "CONTINENT") {
			if (line == "")
				continue;
			std::vector<std::string> splitstr = split(line, '=');
			
			string name = splitstr[0];
			Continent *continent = new Continent(name);
			continents[name] = continent;
			map->addContinent(continent);
			
		} else if (current == "TERRITORIES") {
			if (line == "")
				continue;
			std::vector<std::string> splitstr = split(line, ',');
			
			string name = splitstr[0];
			int x = atoi(splitstr[1].c_str());
			int y = atoi(splitstr[2].c_str());
			Country *country = new Country(name, x, y);
			countries[name] = country;

			string continentName = splitstr[3];
			continents[continentName]->addCountry(country);
			
			vector<string> neighborCountries;
			for (int i = 4; i < splitstr.size(); i++) {
				neighborCountries.push_back(splitstr[i]);
			}
			neighbors[name] = neighborCountries;
		}
	}
	// Link the countries
	for (std::map<string, vector<string> >::iterator it=neighbors.begin(); it!=neighbors.end(); ++it) {
		string countryName = it->first;
		vector<string> neighborNames = it->second;
		Country *c = countries[countryName];
		for (int i = 0; i < neighborNames.size(); i++) {
			c->addNeighbor(countries[neighborNames[i]]);
		}
	}
}
void MapLoader::displayMap()
{
//
}

bool MapLoader::isValid()
{
// need to do loadmap to check for exception throwing
	return true;
}
// Check lab for instruction
