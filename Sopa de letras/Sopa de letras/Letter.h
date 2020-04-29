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
	void Set_letter(char letter) { this->letter = letter; };
	void Set_ascii(int ascii) { this->ascii = ascii; };
	void Set_letter_case(int letter_case) { this->letter_case = letter_case; };
	void Set_point(Point point) { this->point = point; };
	void Set_L(char letter, int ascii, int letter_case, Point point);
	void Set_L(char letter, int ascii, int letter_case);
	char Get_letter(void) const { return letter; };
	int Get_ascii(void) const { return ascii; };
	int Get_letter_case(void) const { return letter_case; };
	Point Get_point(void) const { return point; };
	void Rand_letter(void);
	void Read(ifstream& is);
	void Save(ofstream& os);
	void operator=(Letter l);
	void operator=(char c);
	friend ostream& operator<<(ostream& os, Letter l);
};

