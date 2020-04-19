#pragma once
#include "Letter.h"
#include <string>
#include <algorithm>

#define NOT_USED 0
#define NOT_FOUND 1
#define FOUND 2

class Word
{
private:
	string word;
	int orientation; // 1 - HF, 2 - HT, 3 - VB, 4 - VC, 5 - D1B, 6 - D1C, 7 - D2B, 8 - D2C
	int state;
	Point initial_point;
public:
	Word();
	Word(string word);
	Word(string word, int orientation, int state, Point initial_point);
	virtual ~Word();
	void Set_word(string word) { this->word = word; };
	void Set_orientation(int orientation) { this->orientation = orientation; };
	void Set_state(int state) { this->state = state; };
	void Set_initial_point(Point initial_point) { this->initial_point = initial_point; };
	void Set_initial_point(int x, int y);
	string Get_word(void) const { return word; };
	int Get_orientation(void) const { return orientation; };
	int Get_state(void) const { return state; };
	Point Get_initial_point(void) const { return initial_point; };
	void Ask2Set_W(void);
	void Upper_Case(void);
	size_t size(void);
	int Verify_letter(char c);
	bool operator==(Word w);
	void operator=(Word w);
	friend ostream& operator<<(ostream& os, Word w);
};

