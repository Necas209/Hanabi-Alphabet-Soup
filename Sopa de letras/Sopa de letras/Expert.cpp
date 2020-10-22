#include "Expert.h"

Expert::Expert()
{
}

Expert::~Expert()
{
}

void Expert::Final_Score(chrono::duration<double> elapsed, int num_words)
{
	double bonus;
	int max_time;
	max_time = (num_words * 60);
	bonus = (max_time - elapsed.count()) / 10;
	score += bonus;
}

void Expert::Save(ofstream& os)
{
	os << "E: ";
	Player::Save(os);
}
