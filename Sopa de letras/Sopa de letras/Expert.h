#pragma once
#include "Player.h"

class Expert :
	public Player
{
public:
	Expert();
	~Expert();
	void Score(bool flag, chrono::duration<double> elapsed, double max_time);
	void Save(ofstream& os);
};