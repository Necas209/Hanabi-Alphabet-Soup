#include "Board.h"

Board::Board(HWND hWnd)
	:DimX(0), DimY(0), n(0)
{
	Board_Menu(hWnd);
}

Board::~Board()
{
	matrix.clear();
	list.clear();
}

void Board::Board_Menu(HWND hWnd)
{
	Board_Title = CreateWindowA("STATIC", "Dimensões do tabuleiro",
		WS_VISIBLE | WS_CHILD | WS_BORDER, 
		350, 200, 200, 30,
		hWnd, nullptr, nullptr, nullptr);
	_DimX = CreateWindowA("STATIC", "Dimensão X",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		300, 300, 100, 30,
		hWnd, nullptr, nullptr, nullptr);
	DimX_Input = CreateWindowA("EDIT", "",
		WS_BORDER | WS_CHILD | WS_VISIBLE,
		400, 300, 200, 30,
		hWnd, (HMENU)ID_DIMX, nullptr, nullptr);
	_DimY = CreateWindowA("STATIC", "Dimensão Y",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		300, 400, 100, 30,
		hWnd, nullptr, nullptr, nullptr);
	DimY_Input = CreateWindowA("EDIT", "",
		WS_BORDER | WS_CHILD | WS_VISIBLE,
		400, 400, 200, 30,
		hWnd, (HMENU)ID_DIMY, nullptr, nullptr);
	Board_Button = CreateWindowA("BUTTON", "OK",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		420, 500, 50, 50,
		hWnd, (HMENU)ID_BOARD_BUTTON, nullptr, nullptr);
}

void Board::Create_matrix()
{
	char l = ' ';
	matrix.resize(DimY, vector<Letter>(DimX));
	_Board = new HWND*[DimY];
	for (int i = 0; i < DimY; i++)
		_Board[i] = new HWND[DimX];
	X_Bar = new HWND[DimX];
	Y_Bar = new HWND[DimY];
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
		l = list[i].size();
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
	}/*
	for (int i = 0; i < DimY; i++)
	{
		for (int j = 0; j < DimX; j++)
		{
			if (matrix[i][j].Get_letter() == ' ')
				matrix[i][j].Rand_letter();
		}
	}*/
}

void Board::Show_matrix(HWND hWnd)
{
	char* s;
	string p;
	for (int y = 0; y < DimY; y++)
	{
		for (int x = 0; x < DimX; x++)
		{
			p = matrix[y][x].Get_letter();
			_Board[y][x] = CreateWindowA("STATIC", &p[0],
				WS_VISIBLE | WS_CHILD | WS_BORDER,
				125 + 25 * y, 125 + 25 * x, 20, 20,
				hWnd, nullptr, nullptr, nullptr);
		}
	}
	for (int x = 0; x < DimX; x++)
	{
		p = to_string(x);
		s = &p[0];
		X_Bar[x] = CreateWindowA("STATIC", s,
			WS_VISIBLE | WS_CHILD,
			100, 125 + 25 * x, 20, 20,
			hWnd, nullptr, nullptr, nullptr);
	}
	for (int y = 0; y < DimY; y++)
	{
		p = to_string(y);
		s = &p[0];
		Y_Bar[y] = CreateWindowA("STATIC", s,
			WS_VISIBLE | WS_CHILD,
			125 + 25 * y, 100, 20, 20,
			hWnd, nullptr, nullptr, nullptr);
	}
}

int Board::Get_n_used(void)
{
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		if (list[i].Get_state() != NOT_USED)
			k++;
	}
	return k;
}

void Board::Set_Board(void)
{
	DimX = n_dimx;
	DimY = n_dimy;
	DestroyWindow(Board_Title);
	DestroyWindow(_DimX);
	DestroyWindow(_DimY);
	DestroyWindow(DimX_Input);
	DestroyWindow(DimY_Input);
	DestroyWindow(Board_Button);
}

void Board::Load_list()
{
	string aux;
	ifstream file;
	file.open("distritos.txt");
	while (!file.eof())
	{
		getline(file, aux);
		list.push_back(Word(aux));
	}
	n = list.size();
	file.close();
}

void Board::Show_list()
{
	for (int i = 0; i < n; i++)
	{
		if(list[i].Get_state() == FOUND)
			cout << list[i] << endl;
	}
}

bool Board::Check_Crossing(int i)
{
	int x = list[i].Get_initial_point().Get_x();
	int y = list[i].Get_initial_point().Get_y();
	int l = list[i].size();
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
	char l = matrix[y][x].Get_letter();
	char c = list[i].Get_word()[k];
	return (l == ' ' or l == c);
}

void Board::Insert_Word(int i)
{
	int x = list[i].Get_initial_point().Get_x();
	int y = list[i].Get_initial_point().Get_y();
	int l = list[i].size();
	int o = list[i].Get_orientation();
	list[i].Set_state(NOT_FOUND);
	switch (o)
	{
	case FRONT:
		for (int j = x; j < (x + l); j++)
			matrix[y][j] = list[i].Get_word()[j - x];
		break;
	case BACK:
		for (int j = x; j > (x - l); j--)
			matrix[y][j] = list[i].Get_word()[x - j];
		break;
	case DOWN:
		for (int j = y; j < (y + l); j++)
			matrix[j][x] = list[i].Get_word()[j - y];
		break;
	case UP:
		for (int j = y; j > (y - l); j--)
			matrix[j][x] = list[i].Get_word()[y - j];
		break;
	case FRONT_DOWN:
		for (int j1 = x, j2 = y; j1 < (x + l) and j2 < (y + l); j1++, j2++)
			matrix[j2][j1] = list[i].Get_word()[j1 - x];
		break;
	case BACK_UP:
		for (int j1 = x, j2 = y; j1 > (x - l) and j2 > (y - l); j1--, j2--)
			matrix[j2][j1] = list[i].Get_word()[x - j1];
		break;
	case BACK_DOWN:
		for (int j1 = x, j2 = y; j1 > (x - l) and j2 < (y + l); j1--, j2++)
			matrix[j2][j1] = list[i].Get_word()[j2 - y];
		break;
	case FRONT_UP:
		for (int j1 = x, j2 = y; j1 < (x + l) and j2 > (y - l); j1++, j2--)
			matrix[j2][j1] = list[i].Get_word()[j1 - x];
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
			if (list[i].Get_state() != FOUND)
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
	cout << endl << " A palavra não está na sopa de letras." << endl;
	return false;
}
