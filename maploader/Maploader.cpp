#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

#include "Maploader.h"

using namespace std;

const int MAXLINE=256;


template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

MapLoader::MapLoader()
{
	map = new Map();
}

void MapLoader::loadMap(string filename){
//Need map classes with continents and countries
// creation of fstream
	//open file
	//check line by line by putting delimeters for [ ] symbols and " " space. Register everything as a stringe and parse it into the new objects created by Sunny
	
	ifstream inFile (filename.c_str());
	string line;
	string current;
	while (getline(inFile, line)) {
		if (line == "[Map]") {
			string line1;
			current = "MAP";
		} else if (line == "[Continents]") {
			string line2;
			current = "CONTINENT";
		} else if (line == "[Territories]") {
			string line3;
			current = "TERRITORIES";
		} else if (current == "MAP") {
			// TODO: Parse map line
		} else if (current == "CONTINENT") {
			// TODO: Parse continent line
		} else if (current == "TERRITORIES") {
			// TODO: Parse territories line
		}
	}
}
void displayMap(){
//
}

bool isValid(){
// need to do loadmap to check for exception throwing
	return true;
}
// Check lab for instructions

int main() {
	MapLoader *ml = new MapLoader();
	ml->loadMap("World.map");
	return 0;
}
