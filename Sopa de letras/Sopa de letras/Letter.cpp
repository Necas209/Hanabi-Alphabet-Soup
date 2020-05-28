#include "Letter.h"

Letter::Letter()
	:letter(' '), ascii(' '), letter_case(LOWERCASE), state(NOT_USED)
{
}

Letter::~Letter()
{
}

void Letter::Set_point(int x, int y)
{
	point.Set_P(x, y);
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
	is >> c >> state;
	point.Read(is);
	Set_L(c, c, Upper_lower(c));
}

void Letter::Save(ofstream& os)
{
	os << letter << ' ' << state << ' ';
	point.Save(os);
	os << ';';
}

void Letter::ShowLetter(void)
{
	cout << "Letra: " << letter << endl;
	point.ShowPoint();
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

bool Letter::operator==(char c)
{
	return (letter == c);
}

ostream& operator<<(ostream& os, Letter l)
{
	os << l.letter << ' ';
	return os;
}
