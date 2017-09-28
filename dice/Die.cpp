#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Die.h"

using namespace std;

Die::Die()
{
}


Die::~Die()
{
}

int Die::roll() {
	total_rolls++;
	srand(clock());
	int value = (rand() % 6) + 1;
	value_count[value-1]+=1;
	return value;
}

void Die::stats() {
	int roll_value=0;
	for each (int roll_count in value_count)
	{
		roll_value++;
		cout << roll_value <<  " : " << (roll_count / max(total_rolls,1))*100 <<"%"<<endl;
	}
}

