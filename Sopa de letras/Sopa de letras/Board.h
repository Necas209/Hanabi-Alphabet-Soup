#pragma once
#include "Letter.h"
#include "Word.h"

class Board
{
private:
	vector<vector<Letter>> matrix;
	vector<Word> list;
	int DimX;
	int DimY;
	int n;          // numero de palavras
public:
	Board();
	virtual ~Board();
	void Set_matrix(vector<vector<Letter>> matrix) { this->matrix = matrix; };
	void Set_list(vector<Word> list) { this->list = list; };
	void Set_DimX(int DimX) { this->DimX = DimX; };
	void Set_DimY(int DimY) { this->DimY = DimY; };
	void Set_n(int n) { this->n = n; };
	vector<vector<Letter>> Get_matrix(void) const { return matrix; };
	vector<Word> Get_list(void) const { return list; };
	int Get_DimX(void) const { return DimX; };
	int Get_DimY(void) const { return DimY; };
	int Get_n(void) const { return n; };
	void Ask_DimX(void);
	void Ask_DimY(void);
	void Create_matrix(void);
	void Fill_matrix(void);
	void Show_matrix(void);
	void Load_list(void);
	void Show_list(void);
	bool Check_If_It_Fits(int i);
	bool Check_Crossing(int i);
	bool Check_Letter(int i, int x, int y, int k);
	void Insert_Word(int i);
	bool Check_If_Word_Is_Present(string p);
};