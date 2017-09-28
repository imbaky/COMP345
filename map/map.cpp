#include "map.h"

Country::Country(string countryName, int x, int y) :
	name(countryName), posX(x), posY(y)
{}

void Country::addNeighbor(Country *country) {
	if (!hasNeighbor
	neighbors.push_back(country);
	country->addNeighbor(this);
}

bool Country::hasNeighbor(Country *country) {
	if(std::find(v.begin(), v.end(), x) != v.end()) {
		/* v contains x */
	} else {
		/* v does not contain x */
	}
}

Continent::Continent(string continentName) : name(continentName) {}

