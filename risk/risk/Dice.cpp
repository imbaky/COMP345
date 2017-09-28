#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include "Dice.h"
#include "Die.h"

using namespace std;

Dice::Dice(int num) {
	dies=new Die [num];
	for (int i = 0; i<num; i++) {
		dies[i] = new Die(i);
	}
}
int Dice::roll() {
	int sum=0;
	for each(Die a: dies) {
		sum+=a.roll();
		a.stats();
	}
	return sum;
}