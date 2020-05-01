#pragma once
#include "Letter.h"
#include "Word.h"
#include <vector>
#include <thread>
#include <chrono>

HWND Board_Title, _DimX, DimX_Input, _DimY, DimY_Input, Board_Button;
HWND** _Board;
HWND* X_Bar, * Y_Bar;

char b_dimx[3], b_dimy[3];
int n_dimx, n_dimy;

class Board
{
private:
	vector<vector<Letter>> matrix;
	vector<Word> list;
	int DimX;
	int DimY;
	int n;          // numero de palavras
public:
	Board(HWND hWnd);
	virtual ~Board();
	void Board_Menu(HWND hWnd);
	int Get_n_used(void);
	void Set_Board(void);
	void Create_matrix(void);
	void Fill_matrix(void);
	void Show_matrix(HWND hWnd);
	void Load_list(void);
	void Show_list(void);
	bool Check_Crossing(int i);
	bool Check_Letter(int i, int x, int y, int k);
	void Insert_Word(int i);
	bool Check_If_Word_Is_Present(Word w);
};