//
// Created by Mihai Damaschin on 26/09/17.
//
#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <string>

#include "map.h"

using namespace std;

class MapLoader {
public:
	MapLoader();
	void loadMap(string mapname);
	void displayMap();
	bool isValid();
	Map *getMap();
private:
	Map *map;
	string author;
	string image;
	string wrap;
	string scroll;
	string warn;
};

#endif
