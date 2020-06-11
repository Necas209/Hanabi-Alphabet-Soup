#include "Expert.h"

Expert::Expert()
{
}

Expert::~Expert()
{
}

void Expert::Score(bool flag, chrono::duration<double> elapsed, double max_time)
{
	if (!flag and score > 0)
		score--;
	else if (flag)
	{
		score++;
		if (elapsed.count() < 30)
			score += 5;
	}
}

void Expert::Save(ofstream& os)
{
	os << "E: ";
	Player::Save(os);
}
