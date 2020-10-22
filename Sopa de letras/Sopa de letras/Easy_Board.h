#pragma once
#include "Board.h"

class Easy_Board :
	public Board
{
public:
	Easy_Board();
	~Easy_Board();
	void Ask_DimX(void);
	void Ask_DimY(void);
	void Create_matrix(void);
	void Fill_matrix(void);
	void Show_list(void);
	void Save(ofstream& os);
};

