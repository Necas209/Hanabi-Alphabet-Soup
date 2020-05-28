#include "Beginner.h"

Beginner::Beginner()
{
}

Beginner::~Beginner()
{
}

void Beginner::Score()
{
}

void Beginner::Save(ofstream& os)
{
	os << "B: ";
	Player::Save(os);
}
