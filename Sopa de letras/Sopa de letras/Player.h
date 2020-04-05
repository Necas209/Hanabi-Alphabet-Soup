#pragma once
#include <iostream>

using namespace std;

class Player
{
private:
	string name;
	int age;
	int score;
public:
	Player();
	Player(string n, int id, int p);
	virtual ~Player();
	void Set_name(string name) { this->name = name; };
	void Set_age(int age) { this->age = age; };
	void Set_score(int score) { this->score = score; };
	string Get_name(void) const { return name; };
	int Get_age(void) const { return age; };
	int Get_score(void) const { return score; };
	string Ask_name(void);
	int Ask_age(void);
	void Increase_score(void);
	friend ostream& operator<<(ostream& os, Player* player);
};