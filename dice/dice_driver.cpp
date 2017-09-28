#include "Die.h"
#include "Dice.h"
#include <iostream>
using namespace std;

int main()
{
	Dice *a = new Dice(3);
	a->roll();
	return 0;
}

