#pragma once
#include "Point.h"
#include <iostream>

using namespace std;

class Letter
{
private:
	char letter;
	int ascii;
	int M_m;    // 0 - minuscula, 1 - maiuscula
	Point point;
public:
	Letter();
	Letter(char letra, Point ponto, int ascii, int M_m);
	virtual ~Letter();
	void Set_letra(char letter) { this->letter = letter; };
	void Set_ascii(int ascii) { this->ascii = ascii; };
	void Set_M_m(int M_m) { this->M_m = M_m; };
	void Set_point(Point point) { this->point = point; };
	void Set_Letter(char letter, int ascii, int M_m, Point point);
	void Set_Letter(char letter, int ascii, int M_m);
	char Get_letter(void) const { return letter; };
	int Get_ascii(void) const { return ascii; };
	int Get_M_m(void) const { return M_m; };
	Point Get_point(void) const { return point; };
	void Rand_letter(void);
	void operator=(Letter l);
	void operator=(char c);
	friend ostream& operator<<(ostream& os, Letter l);
};

