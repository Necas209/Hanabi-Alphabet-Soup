#include "Board.h"
#include <fstream>

Board::Board()
	:DimX(0), DimY(0), n(0)
{
	Ask_DimX();
	Ask_DimY();
}

Board::~Board()
{
	matrix.clear();
	list.clear();
}

void Board::Create_matrix()
{
	char l = ' ';
	matrix.resize(DimY, vector<Letter>(DimX));
	for (int i = 0; i < DimY; i++) 
	{
		for (int j = 0; j < DimX; j++) 
			matrix[i][j] = Letter(l, Point(j, i), l, 0);
	}
}

void Board::Fill_matrix(void)
{
	srand((unsigned)time(nullptr));
	for (int i = 0; i < n; i++) {
		do {
			list[i].Set_initial_point(rand() % DimX, rand() % DimY);
			list[i].Set_orientation(rand() % 8 + 1);
		} while (!Check_If_It_Fits(i));
		Insert_Word(i);
	}
	for (int i = 0; i < DimY; i++)
	{
		for (int j = 0; j < DimX; j++)
		{
			if (matrix[i][j].Get_letter() == ' ')
				matrix[i][j].Rand_letter(j, i);
		}
	}
}

void Board::Show_matrix()
{
	for (int i = 0; i < DimY; i++) 
	{
		for (int j = 0; j < DimX; j++)
			cout << matrix[i][j];
		cout << endl;
	}
}

void Board::Ask_DimX() 
{
	int dim_x;
	cout << endl << "Insira a dimensão X da matriz: ";
	cin >> dim_x;
	if (dim_x <= 0)
	{
		cout << " Dimensão inválida." << endl;
		Ask_DimX();
	}
	else
		Set_DimX(dim_x);
}

void Board::Ask_DimY()
{
	int dim_y;
	cout << endl << "Insira a dimensão Y da matriz: ";
	cin >> dim_y;
	if (dim_y <= 0)
	{
		cout << " Dimensão inválida." << endl;
		Ask_DimY();
	}
	else
		Set_DimY(dim_y);
}

void Board::Load_list()
{
	string aux;
	ifstream file;
	file.open("lista.txt");
	while (!file.eof())
	{
		getline(file, aux);
		list.push_back(Word(aux));
		n++;
	}
	file.close();
}

void Board::Show_list()
{
	for (int i = 0; i < n; i++)
		cout << list[i] << endl;
}

bool Board::Check_If_It_Fits(int i)
{
	int x = list[i].Get_initial_point().Get_x();
	int y = list[i].Get_initial_point().Get_y();
	int l = list[i].Get_word().length();
	int o = list[i].Get_orientation();
	switch (o)
	{
	case 1:
		if ((x + l) > DimX)
			return 0;
		break;
	case 2:
		if ((x + 1 - l) < 0)
			return 0;
		break;
	case 3:
		if ((y + l) > DimY)
			return 0;
		break;
	case 4:
		if ((y + 1 - l) < 0)
			return 0;
		break;
	case 5:
		if ((x + l) > DimX or (y + l) > DimY)
			return 0;
		break;
	case 6:
		if ((x + 1 - l) < 0 or (y + 1 - l) < 0)
			return 0;
		break;
	case 7:
		if ((x + 1 - l) < 0 or (y + l) > DimY)
			return 0;
		break;
	case 8:
		if ((x + l) > DimX or (y + 1 - l) < 0)
			return 0;
		break;
	}
	return Check_Crossing(i);
}

bool Board::Check_Crossing(int i)
{
	int x = list[i].Get_initial_point().Get_x();
	int y = list[i].Get_initial_point().Get_y();
	int l = list[i].Get_word().length();
	int o = list[i].Get_orientation();
	if (i == 0)
		return 1;
	switch (o) 
	{
	case 1:
		for (int j = x; j < (x + l); j++) {
			if (!Check_Letter(i, j, y, j-x))
				return false;
		}
		break;
	case 2:
		for (int j = x; j > (x - l); j--) {
			if (!Check_Letter(i, j, y, x-j))
				return false;
		}
		break;
	case 3:
		for (int j = y; j < (y + l); j++) {
			if (!Check_Letter(i, x, j, j-y))
				return false;
		}
		break;
	case 4:
		for (int j = y; j > (y - l); j--) {
			if (!Check_Letter(i, x, j, y-j))
				return false;
		}
		break;
	case 5:
		for (int j1 = x, j2 = y; j1 < (x + l) and j2 < (y + l); j1++, j2++) {
			if (!Check_Letter(i, j1, j2, j1-x))
				return false;
		}
		break;
	case 6:
		for (int j1 = x, j2 = y; j1 > (x - l) and j2 > (y - l); j1--, j2--) {
			if (!Check_Letter(i, j1, j2, x-j1))
				return false;
		}
		break;
	case 7:
		for (int j1 = x, j2 = y; j1 > (x - l) and j2 < (y + l); j1--, j2++) {
			if (!Check_Letter(i, j1, j2, x-j1))
				return false;
		}
		break;
	case 8:
		for (int j1 = x, j2 = y; j1 < (x + l) and j2 > (y - l); j1++, j2--) {
			if (!Check_Letter(i, j1, j2, j1-x))
				return false;
		}
		break;
	}
	return true;
}

bool Board::Check_Letter(int i, int x, int y, int k)
{
	char l = matrix[y][x].Get_letter();
	char c = list[i].Get_word()[k];
	return (l == ' ' or l == c);
}

void Board::Insert_Word(int i)
{
	int x = list[i].Get_initial_point().Get_x();
	int y = list[i].Get_initial_point().Get_y();
	int l = list[i].Get_word().length();
	int o = list[i].Get_orientation();
	switch (o)
	{
	case 1:
		for (int j = x; j < (x + l); j++)
			matrix[y][j] = list[i].Get_word()[j - x];
		break;
	case 2:
		for (int j = x, k = 0; j > (x - l) and k < l; j--, k++)
			matrix[y][j] = list[i].Get_word()[k];
		break;
	case 3:
		for (int j = y; j < (y + l); j++)
			matrix[j][x] = list[i].Get_word()[j - y];
		break;
	case 4:
		for (int j = y, k = 0; j > (y - l) and k < l; j--, k++)
			matrix[j][x] = list[i].Get_word()[k];
		break;
	case 5:
		for (int j1 = x, j2 = y; j1 < (x + l) and j2 < (y + l); j1++, j2++)
			matrix[j2][j1] = list[i].Get_word()[j1 - x];
		break;
	case 6:
		for (int j1 = x, j2 = y, k = 0; j1 > (x - l) and j2 > (y - l) and k < l; j1--, j2--, k++)
			matrix[j2][j1] = list[i].Get_word()[k];
		break;
	case 7:
		for (int j1 = x, j2 = y; j1 > (x - l) and j2 < (y + l); j1--, j2++)
			matrix[j2][j1] = list[i].Get_word()[j2 - y];
		break;
	case 8:
		for (int j1 = x, j2 = y; j1 < (x + l) and j2 > (y - l); j1++, j2--)
			matrix[j2][j1] = list[i].Get_word()[j1 - x];
		break;
	}
}

bool Board::Check_If_Word_Is_Present(string p)
{
	for (int i = 0; i < p.length(); i++)
	{
		if (p[i] >= 'a' and p[i] <= 'z')
			p[i] -= 32;
	}
	for (int i = 0; i < n; i++)
	{
		if (p == list[i].Get_word())
		{
			list[i].Set_state(true);
			return true;
		}
	}
	return false;
}
