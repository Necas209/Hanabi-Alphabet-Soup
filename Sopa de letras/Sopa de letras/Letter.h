#pragma once
#include "Point.h"
#include <iostream>

#define LOWERCASE 0
#define UPPERCASE 1
#define NOT_USED 0

class Letter
{
private:
	char letter;
	int ascii;
	int letter_case;  // 0 - minuscula, 1 - maiuscula
	int* state;
	Point point;
public:
	Letter();
	Letter(char letra, Point ponto, int ascii, int M_m);
	virtual ~Letter();
	void Set_L(char letter, int ascii, int letter_case);
	void Set_state(int* state) { this->state = state; };
	int* Get_state(void) const { return state; };
	void Rand_letter(void);
	void Read(ifstream& is);
	void Save(ofstream& os);
	void operator=(Letter l);
	void operator=(char c);
	bool operator==(char c);
	friend ostream& operator<<(ostream& os, Letter l);
};

