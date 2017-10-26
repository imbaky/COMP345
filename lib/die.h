#ifndef DIE_H
#define DIE_H

#include <map>

using namespace std;

class Die {
public:
	Die();
	~Die();

	int roll();
	// Return a map of the current roll count where keys are values from 1 to 6
	map<int, int> stats();
	// Print current roll count
	void printStats();
private:
	int totalRolls;
	map<int, int> valueCount;
};

#endif
