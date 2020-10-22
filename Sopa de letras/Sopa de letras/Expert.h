#pragma once
#include "Player.h"

class Expert :
	public Player
{
public:
	Expert();
	~Expert();
	void Final_Score(chrono::duration<double> elapsed, int num_words);
	void Save(ofstream& os);
};