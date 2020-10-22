#include "Board.h"

Board::Board()
	:matrix(nullptr), DimX(0), DimY(0), num_words(0)
{
}

Board::~Board()
{
	for (int i = 0; i < DimY; i++)
		delete[] matrix[i];
	delete[] matrix;
	list.clear();
}

void Board::Create_matrix()
{
	Ask_DimX();
	Ask_DimY();
	matrix = new Letter*[DimY];
	for (int i = 0; i < DimY; i++) 
	{
		matrix[i] = new Letter[DimX];
		for (int j = 0; j < DimX; j++) 
			matrix[i][j].Set_point(j, i);
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
			if (matrix[i][j].Get_state() == FOUND)
				setForeColor(MY_COLOR_LIGTH_RED);
			cout << matrix[i][j];
			resetColor();
		}
		cout << endl;
	}
}

int Board::Number_USED(void)
{
	int k = 0;
	for (int i = 0; i < num_words; i++)
	{
		if (list[i] != NOT_USED)
			k++;
	}
	return k;
}

int Board::Number_NOT_FOUND()
{
	int k = 0;
	for (int i = 0; i < num_words; i++)
	{
		if (list[i] == NOT_FOUND)
			k++;
	}
	return k;
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
			num_words = list.size();
		}
		file.close();
	}
}

void Board::Show_list()
{
	int k = 0;
	gotoxy(2 * DimX + 20, 1);
	cout << "Palavras encontradas: " << Number_USED()-Number_NOT_FOUND() << " de " << Number_USED();
	for (int i = 0; i < num_words; i++)
	{
		if (list[i] == FOUND)
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
		return true;
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
	int x, y, l, o, s;
	string w = list[i].Get_word();
	x = list[i].Get_initial_x();
	y = list[i].Get_initial_y();
	l = list[i].length();
	o = list[i].Get_orientation();
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

void Board::Read(ifstream& is)
{
	char c;
	string s;
	getline(is, s);
	is >> DimX >> DimY;
	matrix = new Letter * [DimY];
	for (int i = 0; i < DimY; i++)
		matrix[i] = new Letter[DimX];
	getline(is, s);
	getline(is, s);
	for (int y = 0; y < DimY; y++)
	{
		for (int x = 0; x < DimX; x++)
		{
			matrix[y][x].Read(is);
			is >> c;
		}
		getline(is, s);
	}
	getline(is, s);
	is >> num_words;
	getline(is, s);
	list.resize(num_words);
	getline(is, s);
	for (int i = 0; i < num_words; i++)
	{
		list[i].Read(is);
		getline(is, s);
	}
}

void Board::Save(ofstream& os)
{
	os << "Dimensions:\n";
	os << DimX << ' ' << DimY << ";\n";
	os << "Letters:\n";
	for (int y = 0; y < DimY; y++)
	{
		for (int x = 0; x < DimX; x++)
			matrix[y][x].Save(os);
		os << endl;
	}
	os << "Number of Words:\n";
	os << num_words << ";\n";
	os << "Words:\n";
	for (int i = 0; i < num_words; i++)
	{
		list[i].Save(os);
		if (i != num_words - 1)
			os << endl;
	}
}

bool Board::Check_If_Word_Is_Present(Word w)
{
	w.Upper_Case();
	for (int i = 0; i < num_words; i++)
	{
		if (w == list[i])
		{
			if (list[i] != FOUND)
			{
				list[i].Set_state(FOUND);
				Insert_Word(i);
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