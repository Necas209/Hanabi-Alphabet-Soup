#pragma once
#include "Letter.h"
#include "Word.h"
#include <vector>
#include <thread>
#include <chrono>

class Board
{
private:
	vector<vector<Letter>> matrix;
	vector<Word> list;
	vector<int> orientations;
	int DimX;
	int DimY;
	int n;          // numero de palavras
public:
	Board();
	virtual ~Board();
	void Set_n(int n) { this->n = n; };
	int Get_n_used(void);
	void Ask_DimX(void);
	void Ask_DimY(void);
	void Create_matrix(void);
	void Fill_matrix(void);
	void Show_matrix(void);
	void Load_list(void);
	void Show_list(void);
	bool Check_Crossing(int i);
	bool Check_Letter(int i, int x, int y, int k);
	void Insert_Word(int i);
	bool Check_If_Word_Is_Present(Word w);
};