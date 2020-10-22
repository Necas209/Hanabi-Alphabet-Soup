#pragma once
#include "functions.h"

class Player
{
protected:
	string name;
	int age;
	int score;
public:
	Player();
	virtual ~Player();
	void Ask_name(void);
	void Ask_age(void);
	void Update_Score(bool flag);
	virtual void Final_Score(chrono::duration<double> elapsed, int num_words) = 0;
	void Show(void);
	virtual void Read(ifstream& is);
	virtual void Save(ofstream& os);
	friend ostream& operator<<(ostream& os, Player& player);
};