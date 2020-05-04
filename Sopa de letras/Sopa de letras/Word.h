#pragma once
#include "Letter.h"

// States
#define NOT_USED 0
#define NOT_FOUND 1
#define FOUND 2
// Orientations
#define NONE 0
#define FRONT 1
#define BACK 2
#define DOWN 3
#define UP 4
#define FRONT_DOWN 5
#define BACK_UP 6
#define BACK_DOWN 7
#define FRONT_UP 8

class Word
{
private:
	string word;
	int orientation;
	int* state;
	Point initial_point;
public:
	Word();
	Word(string word);
	virtual ~Word();
	void Set_word(string word) { this->word = word; };
	void Set_state(int s) { *state = s; };
	string Get_word(void) const { return word; };
	int Get_orientation(void) const { return orientation; };
	int* Get_state(void) const { return state; };
	int Get_initial_x(void);
	int Get_initial_y(void);
	void RandPoint(int DimX, int DimY);
	void RandOrientation(void);
	void Ask2Set_W(void);
	void Upper_Case(void);
	size_t length(void);
	void Read(ifstream& is);
	void Save(ofstream& os);
	bool operator==(Word w);
	void operator=(Word w);
	friend ostream& operator<<(ostream& os, Word w);
};

