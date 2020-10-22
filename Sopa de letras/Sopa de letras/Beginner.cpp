#include "Beginner.h"

Beginner::Beginner()
{
}

Beginner::~Beginner()
{
}

void Beginner::Final_Score(chrono::duration<double> elapsed, int num_words)
{
}

void Beginner::Save(ofstream& os)
{
	os << "B: ";
	Player::Save(os);
}
