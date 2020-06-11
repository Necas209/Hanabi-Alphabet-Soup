#include "Beginner.h"

Beginner::Beginner()
{
}

Beginner::~Beginner()
{
}

void Beginner::Score(bool flag, chrono::duration<double> elapsed, double max_time)
{
	if (flag)
		score++;
}

void Beginner::Save(ofstream& os)
{
	os << "B: ";
	Player::Save(os);
}
