//
// Created by Mihai Damaschin on 26/09/17.
//
#ifndef RISK_MAPLOADER_H
#define RISK_MAPLOADER_H

#include <string>
#include <rpcndr.h>

using namespace std;


class Maploader {
    Map map;
    string author;
    string image;
    string wrap;
    string scroll;
    string warn;

public:
    Maploader();
    void loadMap(string mapname);
    Country country(string country);
    Continent continent(string continent);
    void displayMap();
    boolean isValid();
};

#endif //RISK_MAPLOADER_H
