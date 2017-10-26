#ifndef DICE_H
#define DICE_H

#include <vector>

#include "die.h"

class Dice {
public:
	Dice(int num);
	~Dice();

	// Roll all dices
	int roll();
	// Roll a specific number of dices
	int roll(int n);

	void printStats();
	// Return a map of the current roll count where keys are values from 1 to 6
	// from all dices
	map<int, int> stats();
	// Print total roll count for all dices
	vector<Die *> getDices();
private:
	vector<Die *> dices;
};

#endif
