#include "Hard_Board.h"

Hard_Board::Hard_Board()
{
}

Hard_Board::~Hard_Board()
{
}

void Hard_Board::Fill_matrix(void)
{
	int l;
	srand((unsigned)time(nullptr));
	auto start = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed;
	for (int i = 0; i < num_words; i++)
	{
		l = list[i].length();
		if (l <= DimX and l <= DimY)
		{
			do {
				list[i].RandOrientation();
				list[i].RandPoint(DimX, DimY);
				auto end = chrono::high_resolution_clock::now();
				elapsed = end - start;
			} while (!Check_Crossing(i) and elapsed.count() < 1);
			if (Check_Crossing(i))
			{
				list[i].Set_state(NOT_FOUND);
				Insert_Word(i);
			}
		}
	}
	for (int i = 0; i < DimY; i++)
	{
		for (int j = 0; j < DimX; j++)
		{
			if (matrix[i][j] == ' ')
				matrix[i][j].Rand_letter();
		}
	}
}

void Hard_Board::Show_list(void)
{
	Board::Show_list();
}

void Hard_Board::Save(ofstream& os)
{
	os << "H: ";
	Board::Save(os);
}
