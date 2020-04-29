#include "Word.h"

Word::Word()
	:orientation(NONE), state(NOT_USED)
{
}

Word::Word(string word)
{
	this->word = word;
	state = NOT_USED;
}

Word::~Word()
{
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
	initial_point.Set_P(x, y);
}

void Word::RandOrientation(void)
{
	orientation = rand() % 8 + 1;
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

void Word::Read(ifstream& is)
{
	int o, s;
	string w;
	is >> o >> s;
	initial_point.Read(is);
	getline(is, w, ';');
	Set_orientation(o);
	Set_state(s);
	Set_word(w);
}

void Word::Save(ofstream& os)
{
	os << orientation << state;
	initial_point.Save(os);
	os << word;
}

bool Word::operator==(Word w)
{
	return (this->word == w.word && this->initial_point == w.initial_point);
}

void Word::operator=(Word w)
{
	Set_word(w.word);
	Set_orientation(w.orientation);
	Set_state(w.state);
	this->initial_point.Set_P(w.initial_point);
}

ostream& operator<<(ostream& os, Word w)
{
	os << w.word;
	return os;
}
