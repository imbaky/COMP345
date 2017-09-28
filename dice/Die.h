#ifndef DIE_H
#define DIE_H

#include <map>

using namespace std;

class Die {
public:
	Die();
	~Die();

	int roll();
	void stats();
private:
	int totalRolls;
	map<int, int> valueCount;
};

#endif
