#include "Easy_Board.h"

Easy_Board::Easy_Board()
{
}

Easy_Board::~Easy_Board()
{
}

void Easy_Board::Ask_DimX(void)
{
	int dim_x;
	cout << endl << " Insira a dimensão X da matriz: ";
	cin >> dim_x;
	if (!cin.good() or dim_x < 5)
	{
		PreventLoop();
		Ask_DimX();
	}
	else
		DimX = dim_x;
}

void Easy_Board::Ask_DimY(void)
{
	int dim_y;
	cout << endl << " Insira a dimensão Y da matriz: ";
	cin >> dim_y;
	if (!cin.good() or dim_y < 5)
	{
		PreventLoop();
		Ask_DimY();
	}
	else
		DimY = dim_y;
}

void Easy_Board::Create_matrix(void)
{
	cout << endl << "\tDimensões da sopa de letras mínimas: 5 x 5" << endl;
	Board::Create_matrix();
}

void Easy_Board::Fill_matrix(void)
{
	int orientation[] = { FRONT,DOWN,FRONT_DOWN,FRONT_UP };
	int i = 0, k = 0, l;
	srand((unsigned)time(nullptr));
	auto start = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed;
	while (k < 10 and i < num_words)
	{
		l = list[i].length();
		if (l <= DimX and l <= DimY)
		{
			do {
				list[i].Set_orientation(orientation[rand() % 4]);
				list[i].RandPoint(DimX, DimY);
				auto end = chrono::high_resolution_clock::now();
				elapsed = end - start;
			} while (!Check_Crossing(i) and elapsed.count() < 1);
			if (Check_Crossing(i))
			{
				list[i].Set_state(NOT_FOUND);
				Insert_Word(i);
				k++;
			}
		}
		i++;
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

void Easy_Board::Show_list(void)
{
	int k = 0;
	Board::Show_list();
	gotoxy(2 * DimX + 50, 1);
	cout << "Palavras por encontrar:";
	for (int i = 0; i < num_words; i++)
	{
		if (list[i] == NOT_FOUND)
		{
			gotoxy(2 * DimX + 50, 3 + 2 * k);
			cout << list[i];
			k++;
		}
	}
}

void Easy_Board::Save(ofstream& os)
{
	os << "E: ";
	Board::Save(os);
}
