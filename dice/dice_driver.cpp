#include "die.h"
#include "dice.h"
#include <iostream>

using namespace std;

int main()
{
	// Test individual die
	cout << "=============\n" << "Die d1:\n" << "=============\n";
	Die *d1 = new Die();
	cout << "Roll 1: " << d1->roll() << "\n";
	cout << "Roll 2: " << d1->roll() << "\n";
	cout << "Roll 3: " << d1->roll() << "\n";
	cout << "Roll 4: " << d1->roll() << "\n";
	cout << "Roll 5: " << d1->roll() << "\n";
	cout << "=============\n" << "STATS for d1:\n" << "=============\n";
	d1->printStats();
	cout << "\n";
		
	// Group if dices
	cout << "=============\n" << "3 Dices:\n" << "=============\n";
	Dice *dices = new Dice(3);
	cout << "Rolling 3 dices: " << dices->roll() << "\n";
	cout << "Rolling 3 dices: " << dices->roll() << "\n";
	cout << "Rolling 3 dices: " << dices->roll() << "\n";

	cout << "=============\n" << "STATS for 3 dices:\n" << "=============\n";
	dices->printStats();
	cout << "\n";
	
	return 0;
}
