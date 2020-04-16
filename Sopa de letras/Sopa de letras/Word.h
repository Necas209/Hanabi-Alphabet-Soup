#pragma once
#include "Letter.h"
#include <vector>
#include <string>

using namespace std;

class Word
{
private:
	string word;
	int orientation; // 1 - HF, 2 - HT, 3 - VB, 4 - VC, 5 - D1B, 6 - D1C, 7 - D2B, 8 - D2C
	bool state;   // 0 - por descobrir, 1 - descoberto
	Point initial_point;
public:
	Word();
	Word(string word);
	Word(string word, int orientation, bool state, Point initial_point);
	virtual ~Word();
	void Set_word(string word) { this->word = word; };
	void Set_orientation(int orientation) { this->orientation = orientation; };
	void Set_state(bool state) { this->state = state; };
	void Set_initial_point(Point initial_point) { this->initial_point = initial_point; };
	void Set_initial_point(int x, int y);
	string Get_word(void) const { return word; };
	int Get_orientation(void) const { return orientation; };
	bool Get_state(void) const { return state; };
	Point Get_initial_point(void) const { return initial_point; };
	size_t size(void);
	int Verify_letter(char c);
	void operator=(Word w);
	friend ostream& operator<<(ostream& os, Word w);
};

