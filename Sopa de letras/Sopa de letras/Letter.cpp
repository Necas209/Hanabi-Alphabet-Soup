#include "Letter.h"

Letter::Letter()
	:M_m(-1), ascii(0), letter(' ')
{
}

Letter::Letter(char letter, Point point, int ascii, int M_m)
{
	this->point = point;
	this->letter = letter;
	this->ascii = ascii;
	this->M_m = M_m;
}

Letter::~Letter()
{
}

void Letter::Set_Letter(char letter, int ascii, int M_m, Point point)
{
	Set_letra(letter);
	Set_ascii(ascii);
	Set_M_m(M_m);
	Set_point(point);
}

void Letter::Rand_letter(int x, int y)
{
	char c = rand() % 26 + 65;
	Set_Letter(c, c, 1, Point(x, y));
}

void Letter::operator=(Letter l)
{
	Set_letra(l.Get_letter());
	Set_ascii(l.Get_ascii());
	Set_M_m(l.Get_M_m());
	Set_point(l.Get_point());
}

void Letter::operator=(char c)
{
	this->Set_letra(c);
}

ostream& operator<<(ostream& os, Letter l)
{
	os << l.letter << ' ';
	return os;
}
