#include "Word.h"
#include <ctime>


Word::Word()
	:orientation(NONE), state(NOT_USED)
{
}

Word::Word(string word, int orientation, int state, Point initial_point)
{
	this->word = word;
	this->orientation = orientation;
	this->state = state;
	this->initial_point = initial_point;
}

Word::Word(string word)
{
	this->word = word;
	state = NOT_USED;
}

Word::~Word()
{
}

void Word::Set_initial_point(int x, int y)
{
	initial_point.Set_P(x, y);
}

void Word::RandPoint(int DimX, int DimY)
{
	int x, y;
	int l = word.length();
	int h = l - 1;
	switch (orientation)
	{
	case FRONT:
		x = rand() % (DimX - h);
		y = rand() % DimY;
		break;
	case BACK:
		x = h + rand() % (DimX - h);
		y = rand() % DimY;
		break;
	case DOWN:
		x = rand() % DimX;
		y = rand() % (DimY - h);
		break;
	case UP:
		x = rand() % DimX;
		y = h + rand() % (DimY - h);
		break;
	case FRONT_DOWN:
		x = rand() % (DimX - h);
		y = rand() % (DimY - h);
		break;
	case BACK_UP:
		x = h + rand() % (DimX - h);
		y = h + rand() % (DimY - h);
		break;
	case BACK_DOWN:
		x = h + rand() % (DimX - h);
		y = rand() % (DimY - h);
		break;
	case FRONT_UP:
		x = rand() % (DimX - h);
		y = h + rand() % (DimY - h);
		break;
	}
	this->Set_initial_point(x, y);
}

void Word::Ask2Set_W(void)
{
	cout << endl << " Palavra: ";
	cin.ignore();
	getline(cin, word);
	initial_point.Ask2Set_P();
}

void Word::Upper_Case(void)
{
	transform(word.begin(), word.end(), word.begin(), ::toupper);
}

size_t Word::size(void)
{
	return word.length();
}

int Word::Verify_letter(char c)
{
	return(c < 'a' or c > 'z');
}

bool Word::operator==(Word w)
{
	return (word == w.Get_word() && initial_point == w.Get_initial_point());
}

void Word::operator=(Word w)
{
	Set_word(w.Get_word());
	Set_orientation(w.Get_orientation());
	Set_state(w.Get_state());
	Set_initial_point(w.Get_initial_point());
}

ostream& operator<<(ostream& os, Word w)
{
	os << w.word;
	return os;
}
