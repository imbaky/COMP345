#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "die.h"

using namespace std;

Die::Die() : totalRolls(0) {}

Die::~Die() {}

int Die::roll()
{
	totalRolls++;
	srand(clock());
	int value = (rand() % 6) + 1;	
	valueCount[value]++;
	return value;
}

map<int, int> Die::stats()
{
	return valueCount;
}

void Die::printStats()
{
	cout << "1: " << valueCount[1] << "\n" <<
		"2: " << valueCount[2] << "\n" <<
		"3: " << valueCount[3] << "\n" <<
		"4: " << valueCount[4] << "\n" <<
		"5: " << valueCount[5] << "\n" <<
		"6: " << valueCount[6] << "\n";
}

	
