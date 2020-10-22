#pragma once
#include "Player.h"

class Beginner :
	public Player
{
public:
	Beginner();
	~Beginner();
	void Final_Score(chrono::duration<double> elapsed, int num_words);
	void Save(ofstream& os);
};