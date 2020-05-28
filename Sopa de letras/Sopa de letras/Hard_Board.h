#pragma once
#include "Board.h"

class Hard_Board :
	public Board
{
public:
	Hard_Board();
	~Hard_Board();
	void Fill_matrix(void);
	void Show_list(void);
	void Save(ofstream& os);
};

