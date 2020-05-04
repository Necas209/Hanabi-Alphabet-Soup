#include "Board.h"

Board::Board()
	:DimX(0), DimY(0), n(0)
{
	cout << endl << "\tDimensões da sopa de letras" << endl;
	Ask_DimX();
	Ask_DimY();
}

Board::~Board()
{
	matrix.clear();
	list.clear();
}

void Board::Clear_Board(void)
{
	matrix.clear();
	list.clear();
	orientations.clear();
}

void Board::Create_matrix()
{
	char l = ' ';
	matrix.resize(DimY, vector<Letter>(DimX));
	for (int i = 0; i < DimY; i++) 
	{
		for (int j = 0; j < DimX; j++) 
			matrix[i][j] = Letter(l, Point(j, i), l, LOWERCASE);
	}
}

void Board::Fill_matrix(void)
{
	int l;
	srand((unsigned)time(nullptr));
	auto start = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed;
	for (int i = 0; i < n; i++) 
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
			if(Check_Crossing(i))
				Insert_Word(i);
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

void Board::Show_matrix()
{
	cout << endl << "    ";
	for (int i = 0; i < DimX; i++)
			cout << i % 10 << ' ';
	cout << endl;
	for (int i = 0; i < DimY; i++) 
	{
		cout << "  " << i % 10 << ' ';
		for (int j = 0; j < DimX; j++)
		{
			if (*matrix[i][j].Get_state() == FOUND)
				setForeColor(MY_COLOR_LIGTH_RED);
			cout << matrix[i][j];
			resetColor();
		}
		cout << endl;
	}
}

int Board::Get_n_used(void)
{
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		if (*list[i].Get_state() != NOT_USED)
			k++;
	}
	return k;
}

void Board::Ask_DimX()
{
	int dim_x;
	cout << endl << " Insira a dimensão X da matriz: ";
	cin >> dim_x;
	if (!cin.good())
	{
		PreventLoop();
		Ask_DimX();
	}
	else
	{
		if (dim_x <= 0)
		{
			cout << " Dimensão inválida." << endl;
			Ask_DimX();
		}
		else
			DimX = dim_x;
	}
}

void Board::Ask_DimY()
{
	int dim_y;
	cout << endl << " Insira a dimensão Y da matriz: ";
	cin >> dim_y;
	if (!cin.good())
	{
		PreventLoop();
		Ask_DimY();
	}
	else
	{
		if (dim_y <= 0)
		{
			cout << " Dimensão inválida." << endl;
			Ask_DimY();
		}
		else
			DimY = dim_y;
	}
}

void Board::Load_list()
{
	string aux;
	ifstream file;
	int option, i = 0;
	cout << endl << "\tEscolha o tema da sopa de letras:" << endl;
	cout << endl << " 1 -> Distritos de Portugal" << endl;
	cout << endl << " 2 -> Estados Unidos da América" << endl;
	cout << endl << "\tOpção: ";
	cin >> option;
	if (!cin.good() or (option != 1 and option != 2))
	{
		PreventLoop();
		Load_list();
	}
	else
	{
		switch (option)
		{
		case 1:
			file.open("distritos.txt");
			break;
		case 2:
			file.open("usa.txt");
			break;
		}
		if (!file.is_open())
			cout << endl << "Erro ao abrir o ficheiro." << endl;
		else
		{
			while (!file.eof())
			{
				getline(file, aux);
				list.push_back(Word(aux));
				list[i].Upper_Case();
				i++;
			}
			n = list.size();
		}
		file.close();
	}
}

void Board::Show_list()
{
	int k = 0;
	gotoxy(2 * DimX + 20, 1);
	cout << "Palavras encontradas:";
	for (int i = 0; i < n; i++)
	{
		if (*list[i].Get_state() == FOUND)
		{
			gotoxy(2 * DimX + 20, 3 + 2 * k);
			cout << list[i];
			k++;
		}
	}
}

bool Board::Check_Crossing(int i)
{
	int x = list[i].Get_initial_x();
	int y = list[i].Get_initial_y();
	int l = list[i].length();
	int o = list[i].Get_orientation();
	if (i == 0)
		return 1;
	switch (o) 
	{
	case FRONT:
		for (int j = x; j < (x + l); j++) {
			if (!Check_Letter(i, j, y, j-x))
				return false;
		}
		break;
	case BACK:
		for (int j = x; j > (x - l); j--) {
			if (!Check_Letter(i, j, y, x-j))
				return false;
		}
		break;
	case DOWN:
		for (int j = y; j < (y + l); j++) {
			if (!Check_Letter(i, x, j, j-y))
				return false;
		}
		break;
	case UP:
		for (int j = y; j > (y - l); j--) {
			if (!Check_Letter(i, x, j, y-j))
				return false;
		}
		break;
	case FRONT_DOWN:
		for (int j1 = x, j2 = y; j1 < (x + l) and j2 < (y + l); j1++, j2++) {
			if (!Check_Letter(i, j1, j2, j1-x))
				return false;
		}
		break;
	case BACK_UP:
		for (int j1 = x, j2 = y; j1 > (x - l) and j2 > (y - l); j1--, j2--) {
			if (!Check_Letter(i, j1, j2, x-j1))
				return false;
		}
		break;
	case BACK_DOWN:
		for (int j1 = x, j2 = y; j1 > (x - l) and j2 < (y + l); j1--, j2++) {
			if (!Check_Letter(i, j1, j2, x-j1))
				return false;
		}
		break;
	case FRONT_UP:
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
	Letter l = matrix[y][x];
	char c = list[i].Get_word()[k];
	return (l == ' ' or l == c);
}

void Board::Insert_Word(int i)
{
	int x, y, l, o, *s;
	string w = list[i].Get_word();
	x = list[i].Get_initial_x();
	y = list[i].Get_initial_y();
	l = list[i].length();
	o = list[i].Get_orientation();
	list[i].Set_state(NOT_FOUND);
	s = list[i].Get_state();
	switch (o)
	{
	case FRONT:
		for (int j = x; j < (x + l); j++)
		{
			matrix[y][j] = w[j - x];
			matrix[y][j].Set_state(s);
		}
		break;
	case BACK:
		for (int j = x; j > (x - l); j--)
		{
			matrix[y][j] = w[x - j];
			matrix[y][j].Set_state(s);
		}
		break;
	case DOWN:
		for (int j = y; j < (y + l); j++)
		{
			matrix[j][x] = w[j - y];
			matrix[j][x].Set_state(s);
		}
		break;
	case UP:
		for (int j = y; j > (y - l); j--)
		{
			matrix[j][x] = w[y - j];
			matrix[j][x].Set_state(s);
		}
		break;
	case FRONT_DOWN:
		for (int j1 = x, j2 = y; j1 < (x + l) and j2 < (y + l); j1++, j2++)
		{
			matrix[j2][j1] = w[j1 - x];
			matrix[j2][j1].Set_state(s);
		}
		break;
	case BACK_UP:
		for (int j1 = x, j2 = y; j1 > (x - l) and j2 > (y - l); j1--, j2--)
		{
			matrix[j2][j1] = w[x - j1];
			matrix[j2][j1].Set_state(s);
		}
		break;
	case BACK_DOWN:
		for (int j1 = x, j2 = y; j1 > (x - l) and j2 < (y + l); j1--, j2++)
		{
			matrix[j2][j1] = w[j2 - y];
			matrix[j2][j1].Set_state(s);
		}
		break;
	case FRONT_UP:
		for (int j1 = x, j2 = y; j1 < (x + l) and j2 >(y - l); j1++, j2--)
		{
			matrix[j2][j1] = w[j1 - x];
			matrix[j2][j1].Set_state(s);
		}
		break;
	}
}

bool Board::Check_If_Word_Is_Present(Word w)
{
	w.Upper_Case();
	for (int i = 0; i < n; i++)
	{
		if (w == list[i])
		{
			if (*list[i].Get_state() != FOUND)
			{
				list[i].Set_state(FOUND);
				return true;
			}
			else
			{
				cout << endl << " A palavra já foi encontrada." << endl;
				return false;
			}
		}
	}
	cout << endl << " A palavra não se encontra na sopa de letras." << endl;
	return false;
}