#pragma once
#include "Player.h"

class Expert :
	public Player
{
public:
	Expert();
	~Expert();
	void Score();
	void Save(ofstream& os);
};