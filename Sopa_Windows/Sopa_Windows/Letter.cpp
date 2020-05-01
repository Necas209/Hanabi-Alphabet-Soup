#include "Letter.h"

Letter::Letter()
	:letter_case(LOWERCASE), ascii(' '), letter(' ')
{
}

Letter::Letter(char letter, Point point, int ascii, int letter_case)
{
	this->point = point;
	this->letter = letter;
	this->ascii = ascii;
	this->letter_case = letter_case;
}

Letter::~Letter()
{
}

void Letter::Set_L(char letter, int ascii, int letter_case, Point point)
{
	this->letter;
	this->ascii = ascii;
	this->letter_case = letter_case;
	this->point = point;
}

void Letter::Set_L(char letter, int ascii, int letter_case)
{
	this->letter = letter;
	this->ascii = ascii;
	this->letter_case = letter_case;
}

int Upper_lower(char c)
{
	return (c < 'a' or c > 'z');
}

void Letter::Rand_letter()
{
	char c = rand() % 26 + 65;
	Set_L(c, c, UPPERCASE);
}

void Letter::Read(ifstream& is)
{
	char c;
	is >> c;
	point.Read(is);
	Set_L(c, c, Upper_lower(c));
}

void Letter::Save(ofstream& os)
{
	os << letter;
	point.Save(os);
}

void Letter::operator=(Letter l)
{
	letter = l.letter;
	ascii = l.ascii;
	letter_case = l.letter_case;
	point = l.point;
}

void Letter::operator=(char c)
{
	letter = c;
}

ostream& operator<<(ostream& os, Letter l)
{
	os << l.letter << ' ';
	return os;
}
