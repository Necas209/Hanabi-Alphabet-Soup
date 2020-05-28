#include "Expert.h"

Expert::Expert()
{
}

Expert::~Expert()
{
}

void Expert::Score()
{
}

void Expert::Save(ofstream& os)
{
	os << "E: ";
	Player::Save(os);
}
