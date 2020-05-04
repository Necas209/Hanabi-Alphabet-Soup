#pragma once
#include "functions.h"

class Player
{
private:
	string name;
	int age;
	int score;
public:
	Player();
	virtual ~Player();
	int Get_score(void) const { return score; };
	void Ask_name(void);
	void Ask_age(void);
	void Increase_score(void);
	void Show(void);
	friend ostream& operator<<(ostream& os, Player& player);
};