#pragma once
#include "Letter.h"
#include "Word.h"

class Board
{
protected:
	Letter** matrix;
	vector<Word> list;
	int DimX;
	int DimY;
	int num_words;
public:
	Board();
	virtual ~Board();
	int Get_DimX(void) const { return DimX; };
	int Get_DimY(void) const { return DimY; };
	int Number_USED(void);
	int Number_NOT_FOUND(void);
	virtual void Ask_DimX(void) = 0;
	virtual void Ask_DimY(void) = 0;
	virtual void Create_matrix(void);
	virtual void Fill_matrix(void) = 0;
	virtual void Show_list(void);
	void Show_matrix(void);
	void Load_list(void);
	bool Check_Crossing(int i);
	bool Check_Letter(int i, int x, int y, int k);
	void Insert_Word(int i);
	void Read(ifstream& is);
	virtual void Save(ofstream& os);
	bool Check_If_Word_Is_Present(Word w);
};