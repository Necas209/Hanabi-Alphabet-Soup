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
	virtual void Score() = 0;
	void Show(void);
	virtual void Read(ifstream& is);
	virtual void Save(ofstream& os);
	friend ostream& operator<<(ostream& os, Player& player);
};