#include "Tabuleiro.h"
#include <fstream>

Tabuleiro::Tabuleiro()
	:DimX(0), DimY(0), n(0)
{
	Ask_DimX();
	Ask_DimY();
}

Tabuleiro::~Tabuleiro()
{
	matriz.clear();
	lista.clear();
}

void Tabuleiro::Create_matriz()
{
	char l = ' ';
	matriz.resize(DimY, vector<Letra>(DimX));
	for (int i = 0; i < DimY; i++) 
	{
		for (int j = 0; j < DimX; j++) 
			matriz[i][j] = Letra(l, Ponto(j, i), l, 0);
	}
}

void Tabuleiro::Fill_matriz(void)
{
	srand((unsigned)time(nullptr));
	for (int i = 0; i < n; i++) {
		do {

			lista[i].Set_ponto_inicial(Ponto(rand()%DimX,rand()%DimY));
			lista[i].Set_orientacao(rand() % 8 + 1);
		} while (!CheckIfItFits(i));
		Insert_palavra(i);
	}
	for (int i = 0; i < DimY; i++)
	{
		for (int j = 0; j < DimX; j++)
		{
			matriz[i][j].Set_ponto(Ponto(j, i));
			if (matriz[i][j].Get_letra() == ' ')
				matriz[i][j].RandLetra(j, i);
		}
	}
}

void Tabuleiro::Show_matriz()
{
	for (int i = 0; i < DimY; i++) 
	{
		for (int j = 0; j < DimX; j++)
			cout << matriz[i][j];
		cout << endl;
	}
}

void Tabuleiro::Ask_DimX() 
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

void Tabuleiro::Ask_DimY()
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

void Tabuleiro::Load_lista()
{
	string aux;
	ifstream file;
	int n, i = 0;
	file.open("lista.txt");
	file >> n;
	Set_n(n);
	lista.resize(n);
	file.ignore(1,'\n');
	while (i < n) 
	{
		getline(file, aux);
		lista[i].Set_Palavra(aux);
		i++;
	}
}

void Tabuleiro::Show_lista()
{
	for (int i = 0; i <n; i++) 
	{
		cout << lista[i] << endl;
	}
}

bool Tabuleiro::CheckIfItFits(int i)
{
	int x = lista[i].Get_ponto_inicial().Get_x();
	int y = lista[i].Get_ponto_inicial().Get_y();
	int l = lista[i].Get_palavra().size();
	int o = lista[i].Get_orientacao();
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
	return CheckCrossing(i);
}

bool Tabuleiro::CheckCrossing(int i)
{
	int x = lista[i].Get_ponto_inicial().Get_x();
	int y = lista[i].Get_ponto_inicial().Get_y();
	int l = lista[i].Get_palavra().size();
	int o = lista[i].Get_orientacao();
	if (i == 0)
		return 1;
	switch (o) 
	{
	case 1:
		for (int j = x; j < (x + l); j++) {
			if (!CheckLetter(i, j, y, j-x))
				return false;
		}
		break;
	case 2:
		for (int j = x; j > (x - l); j--) {
			if (!CheckLetter(i, j, y, x-j))
				return false;
		}
		break;
	case 3:
		for (int j = y; j < (y + l); j++) {
			if (!CheckLetter(i, x, j, j-y))
				return false;
		}
		break;
	case 4:
		for (int j = y; j > (y - l); j--) {
			if (!CheckLetter(i, x, j, y-j))
				return false;
		}
		break;
	case 5:
		for (int j1 = x, j2 = y; j1 < (x + l) and j2 < (y + l); j1++, j2++) {
			if (!CheckLetter(i, j1, j2, j1-x))
				return false;
		}
		break;
	case 6:
		for (int j1 = x, j2 = y; j1 > (x - l) and j2 > (y - l); j1--, j2--) {
			if (!CheckLetter(i, j1, j2, x-j1))
				return false;
		}
		break;
	case 7:
		for (int j1 = x, j2 = y; j1 > (x - l) and j2 < (y + l); j1--, j2++) {
			if (!CheckLetter(i, j1, j2, x-j1))
				return false;
		}
		break;
	case 8:
		for (int j1 = x, j2 = y; j1 < (x + l) and j2 > (y - l); j1++, j2--) {
			if (!CheckLetter(i, j1, j2, j1-x))
				return false;
		}
		break;
	}
	return true;
}

bool Tabuleiro::CheckLetter(int i, int x, int y, int k)
{
	char l = matriz[y][x].Get_letra();
	char c = lista[i].Get_string()[k];
	return (l == ' ' or l == c);
}

void Tabuleiro::Insert_palavra(int i)
{
	int x = lista[i].Get_ponto_inicial().Get_x();
	int y = lista[i].Get_ponto_inicial().Get_y();
	int l = lista[i].Get_palavra().size();
	int o = lista[i].Get_orientacao();
	switch (o)
	{
	case 1:
		for (int j = x; j < (x + l); j++)
			matriz[y][j] = lista[i].Get_palavra()[j - x];
		break;
	case 2:
		for (int j = x, k = 0; j > (x - l) and k < l; j--, k++)
			matriz[y][j] = lista[i].Get_palavra()[k];
		break;
	case 3:
		for (int j = y; j < (y + l); j++)
			matriz[j][x] = lista[i].Get_palavra()[j - y];
		break;
	case 4:
		for (int j = y, k = 0; j > (y - l) and k < l; j--, k++)
			matriz[j][x] = lista[i].Get_palavra()[k];
		break;
	case 5:
		for (int j1 = x, j2 = y; j1 < (x + l) and j2 < (y + l); j1++, j2++)
			matriz[j2][j1] = lista[i].Get_palavra()[j1 - x];
		break;
	case 6:
		for (int j1 = x, j2 = y, k = 0; j1 > (x - l) and j2 > (y - l) and k < l; j1--, j2--, k++)
			matriz[j2][j1] = lista[i].Get_palavra()[k];
		break;
	case 7:
		for (int j1 = x, j2 = y; j1 > (x - l) and j2 < (y + l); j1--, j2++)
			matriz[j2][j1] = lista[i].Get_palavra()[j2 - y];
		break;
	case 8:
		for (int j1 = x, j2 = y; j1 < (x + l) and j2 > (y - l); j1++, j2--)
			matriz[j2][j1] = lista[i].Get_palavra()[j1 - x];
		break;
	}
}
