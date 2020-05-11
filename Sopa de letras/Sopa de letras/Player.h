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
	void New_player(void);
	void Ask_name(void);
	void Ask_age(void);
	void Increase_score(void);
	void Show(void);
	virtual void Read(ifstream& is);
	virtual void Save(ofstream& os);
	friend ostream& operator<<(ostream& os, Player& player);
};