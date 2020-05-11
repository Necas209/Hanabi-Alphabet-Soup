#pragma once
#include "Player.h"

class Beginner :
	public Player
{
public:
	Beginner();
	~Beginner();
	void Save(ofstream& os);
};