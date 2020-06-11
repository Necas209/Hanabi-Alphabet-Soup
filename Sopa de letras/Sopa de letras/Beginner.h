#pragma once
#include "Player.h"

class Beginner :
	public Player
{
public:
	Beginner();
	~Beginner();
	void Score(bool flag, chrono::duration<double> elapsed, double max_time);
	void Save(ofstream& os);
};