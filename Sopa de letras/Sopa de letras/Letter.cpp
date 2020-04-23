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
	Set_letter(letter);
	Set_ascii(ascii);
	Set_letter_case(letter_case);
	Set_point(point);
}

void Letter::Set_L(char letter, int ascii, int letter_case)
{
	Set_letter(letter);
	Set_ascii(ascii);
	Set_letter_case(letter_case);
}

void Letter::Rand_letter()
{
	char c = rand() % 26 + 65;
	Set_L(c, c, UPPERCASE);
}

void Letter::operator=(Letter l)
{
	Set_letter(l.Get_letter());
	Set_ascii(l.Get_ascii());
	Set_letter_case(l.Get_letter_case());
	Set_point(l.Get_point());
}

void Letter::operator=(char c)
{
	this->Set_letter(c);
}

ostream& operator<<(ostream& os, Letter l)
{
	os << l.letter << ' ';
	return os;
}
