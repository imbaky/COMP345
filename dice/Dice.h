#ifndef DICE_H
#define DICE_H

#include "Die.h"
class Dice
{
public:
	Dice(int num);
	~Dice();
	int roll();
private:
	Die *dies;
};

#endif
