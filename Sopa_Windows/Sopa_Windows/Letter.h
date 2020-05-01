#pragma once
#include "Point.h"
#include <iostream>

#define LOWERCASE 0
#define UPPERCASE 1

class Letter
{
private:
	char letter;
	int ascii;
	int letter_case;    // 0 - minuscula, 1 - maiuscula
	Point point;
public:
	Letter();
	Letter(char letra, Point ponto, int ascii, int M_m);
	virtual ~Letter();
	void Set_L(char letter, int ascii, int letter_case, Point point);
	void Set_L(char letter, int ascii, int letter_case);
	char Get_letter(void) const { return letter; };
	void Rand_letter(void);
	void Read(ifstream& is);
	void Save(ofstream& os);
	void operator=(Letter l);
	void operator=(char c);
	friend ostream& operator<<(ostream& os, Letter l);
};

