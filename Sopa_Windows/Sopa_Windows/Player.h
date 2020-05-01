#pragma once
#include <iostream>
#include <string>
#include "framework.h"
#include "Sopa_Windows.h"

using namespace std;

char p_name[20], p_age[3];
int n_age;
HWND _Player, _Name, Name_Input, _Age, Age_Input, Player_Button;

class Player
{
private:
	string name;
	int age;
	int score;
public:
	Player(HWND hWnd);
	virtual ~Player();
	int Get_score(void) const { return score; };
	void Set_Player(void);
	void Player_Menu(HWND hWnd);
	void Increase_score(void);
	friend ostream& operator<<(ostream& os, Player& player);
};

class Beginner :
	public Player
{
public:
	Beginner(HWND hWnd);
};

class Expert :
	public Player
{
public:
	Expert(HWND hWnd);
};