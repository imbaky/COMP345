#include <iostream>

#include "Dice.h"
#include "Die.h"

using namespace std;

Dice::Dice(int num)
{
	for (int i = 0; i < num; i++) {
		dices.push_back(new Die());
	}
}

int Dice::roll()
{
	int sum = 0;
	for(int i = 0; i < dices.size(); i++) {
		int roll = dices[i]->roll();
		sum += roll;
	}
	return sum;
}

void Dice::printStats()
{
	map<int, int> valueCount;
	for(int i = 0; i < dices.size(); i++) {
		map<int, int> stats = dices[i]->stats();
		valueCount[1] += stats[1];
		valueCount[2] += stats[2];
		valueCount[3] += stats[3];
		valueCount[4] += stats[4];
		valueCount[5] += stats[5];
		valueCount[6] += stats[6];
	}
	cout << "1: " << valueCount[1] << "\n" <<
		"2: " << valueCount[2] << "\n" <<
		"3: " << valueCount[3] << "\n" <<
		"4: " << valueCount[4] << "\n" <<
		"5: " << valueCount[5] << "\n" <<
		"6: " << valueCount[6] << "\n";
}

map<int, int> Dice::stats()
{
	map<int, int> valueCount;
	for(int i = 0; i < dices.size(); i++) {
		map<int, int> stats = dices[i]->stats();
		valueCount[1] += stats[1];
		valueCount[2] += stats[2];
		valueCount[3] += stats[3];
		valueCount[4] += stats[4];
		valueCount[5] += stats[5];
		valueCount[6] += stats[6];
	}
	return valueCount;
}

vector<Die *> Dice::getDices()
{
	return dices;
}
