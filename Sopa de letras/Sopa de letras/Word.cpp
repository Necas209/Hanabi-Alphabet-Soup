#include "Word.h"
#include <ctime>


Word::Word()
	:orientation(-1), state(false)
{
}

Word::Word(string word, int orientation, bool state, Point initial_point)
{
	this->word = word;
	this->orientation = orientation;
	this->state = state;
	this->initial_point = initial_point;
}

Word::Word(string word)
{
	this->word = word;
}

Word::~Word()
{
}

void Word::Set_initial_point(int x, int y)
{
	initial_point.Set_P(x, y);
}

void Word::Ask2Set_W(void)
{
	cout << endl << "Palavra: ";
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
