#include "Word.h"

Word::Word()
	:orientation(NONE), state(NOT_USED), word("")
{
}

Word::Word(string word)
	:orientation(NONE), state(NOT_USED), word(word)
{
}

Word::~Word()
{
}

int Word::Get_initial_x(void)
{
	return initial_point.Get_x();
}

int Word::Get_initial_y(void)
{
	return initial_point.Get_y();
}

void Word::RandPoint(int DimX, int DimY)
{
	int x = 0, y = 0;
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
	Upper(word);
}

size_t Word::length(void)
{
	return word.length();
}

void Word::Read(ifstream& is)
{
	is >> orientation >> state;
	initial_point.Read(is);
	getline(is, word, ';');
	word.erase(word.begin());
}

void Word::Save(ofstream& os)
{
	os << orientation << ' ';
	os << state << ' ';
	initial_point.Save(os);
	os << ' ' << word << ';';
}

void Word::Show(void)
{
	cout << "Palavra: " << word << endl;
	cout << "Orienta��o: " << orientation << endl;
	cout << "Estado: " << state << endl;
	initial_point.ShowPoint();
}

bool Word::operator==(Word w)
{
	return (this->word == w.word && this->initial_point == w.initial_point);
}

void Word::operator=(Word w)
{
	this->word = w.word;
	this->orientation = w.orientation;
	this->state = w.state;
	this->initial_point = w.initial_point;
}

ostream& operator<<(ostream& os, Word w)
{
	os << w.word;
	return os;
}
