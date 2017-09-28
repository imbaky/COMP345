#pragma once
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

