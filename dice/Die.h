#ifndef DIE_H
#define DIE_H

class Die
{
public:
	Die();

	~Die();

	int roll();
	void stats();
private:
	int total_rolls = 0;
	int value_count[6]{ 0,0,0,0,0,0 };
};

#endif
