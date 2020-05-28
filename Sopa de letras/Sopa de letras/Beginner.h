#pragma once
#include "Player.h"

class Beginner :
	public Player
{
public:
	Beginner();
	~Beginner();
	void Score();
	void Save(ofstream& os);
};