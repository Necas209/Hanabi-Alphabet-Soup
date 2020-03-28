#include "Tabuleiro.h"
#include <ctime>

using namespace std;

Tabuleiro::Tabuleiro()
	:n(0)
{
	Ask_DimX();
	Ask_DimY();
}

Tabuleiro::~Tabuleiro()
{
}

void Tabuleiro::Create_matriz()
{
	char l;
	vector<vector<Letra>> matriz;
	matriz.resize(Get_DimY(), vector<Letra>(Get_DimX()));
	for (int i = 0; i < Get_DimY(); i++) 
	{
		for (int j = 0; j < Get_DimX(); j++) 
		{
			l = ' ';
			matriz[i][j] = Letra(l, Ponto(j, i), l, 0);
		}
	}
	Set_matriz(matriz);
}

void Tabuleiro::Fill_matriz(void)
{
	int l;
	srand((unsigned)time(nullptr));
	for (int i = 0; i < Get_n(); i++) {
		do {
			lista[i].Set_ponto_inicial(Ponto(rand() % Get_DimX(),rand() % Get_DimY()));
			lista[i].RandOrientacao();
		} while (!CheckIfItFits(i));
		Insert_palavra(i);
	}
	for (int i = 0; i < Get_DimY(); i++)
	{
		for (int j = 0; j < Get_DimX(); j++)
		{
			matriz[i][j].Set_ponto(Ponto(j, i));
			if (matriz[i][j].Get_letra() == ' ')
			{
				l = rand() % 26 + 65;
				matriz[i][j] = Letra((char)l, Ponto(j, i), l, 1);
			}
		}
	}
}

void Tabuleiro::Show_matriz()
{
	for (int i = 0; i < Get_DimY(); i++) 
	{
		for (int j = 0; j < Get_DimX(); j++)
			cout << matriz[i][j] << ' ';
		cout << endl;
	}
}

void Tabuleiro::Ask_DimX() {
	int dim_x;
	cout << endl << "PS: Recomenda-se a escolha de dimensões mínimas de 17*17" << endl;
	cout << endl << "Insira a dimensão X da matriz: ";
	cin >> dim_x;
	Set_DimX(dim_x);
}

void Tabuleiro::Ask_DimY()
{
	int dim_y;
	cout << endl << "Insira a dimensão Y da matriz: ";
	cin >> dim_y;
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
	for (int i = 0; i < Get_n(); i++) 
	{
		cout << lista[i] << endl;
	}
}

bool Tabuleiro::CheckIfItFits(int i)
{
	int a = lista[i].Get_ponto_inicial().Get_x();
	int b = lista[i].Get_ponto_inicial().Get_y();
	int c = lista[i].Get_palavra().size();
	int o = lista[i].Get_orientacao();
	switch (o)
	{
	case 1:
		if ((a + c) > Get_DimX())
			return 0;
		break;
	case 2:
		if ((a + 1 - c) < 0)
			return 0;
		break;
	case 3:
		if ((b + c) > Get_DimY())
			return 0;
		break;
	case 4:
		if ((b + 1 - c) < 0)
			return 0;
		break;
	case 5:
		if ((a + c) > Get_DimX() or (b + c) > Get_DimY())
			return 0;
		break;
	case 6:
		if ((a + 1 - c) < 0 or (b + 1 - c) < 0)
			return 0;
		break;
	case 7:
		if ((a + 1 - c) < 0 or (b + c) > Get_DimY())
			return 0;
		break;
	case 8:
		if ((a + c) > Get_DimX() or (b + 1 - c) < 0)
			return 0;
		break;
	}
	return CheckCrossing(i);
}

bool Tabuleiro::CheckCrossing(int i)
{
	int a, b, c, o;
	a = lista[i].Get_ponto_inicial().Get_x();
	b = lista[i].Get_ponto_inicial().Get_y();
	c = lista[i].Get_palavra().size();
	o = lista[i].Get_orientacao();
	if (i == 0)
		return 1;
	switch (o) 
	{
	case 1:
		for (int j = a; j < (a + c); j++) {
			if (!CheckLetter(i, j, b, j-a))
				return false;
		}
		break;
	case 2:
		for (int j = a; j > (a - c); j--) {
			if (!CheckLetter(i, j, b, a-j))
				return false;
		}
		break;
	case 3:
		for (int j = b; j < (b + c); j++) {
			if (!CheckLetter(i, a, j, j-b))
				return false;
		}
		break;
	case 4:
		for (int j = b; j > (b - c); j--) {
			if (!CheckLetter(i, a, j, b-j))
				return false;
		}
		break;
	case 5:
		for (int j1 = a, j2 = b; j1 < (a + c) and j2 < (b + c); j1++, j2++) {
			if (!CheckLetter(i, j1, j2, j1-a))
				return false;
		}
		break;
	case 6:
		for (int j1 = a, j2 = b; j1 > (a - c) and j2 > (b - c); j1--, j2--) {
			if (!CheckLetter(i, j1, j2, a-j1))
				return false;
		}
		break;
	case 7:
		for (int j1 = a, j2 = b; j1 > (a - c) and j2 < (b + c); j1--, j2++) {
			if (!CheckLetter(i, j1, j2, a-j1))
				return false;
		}
		break;
	case 8:
		for (int j1 = a, j2 = b; j1 < (a + c) and j2 > (b - c); j1++, j2--) {
			if (!CheckLetter(i, j1, j2, j1-a))
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
	int a = lista[i].Get_ponto_inicial().Get_x();
	int b = lista[i].Get_ponto_inicial().Get_y();
	int c = lista[i].Get_palavra().size();
	int o = lista[i].Get_orientacao();
	switch (o)
	{
	case 1:
		for (int j = a; j < (a + c); j++)
			matriz[b][j] = lista[i].Get_palavra()[j - a];
		break;
	case 2:
		for (int j = a, k = 0; j > (a - c) and k < c; j--, k++)
			matriz[b][j] = lista[i].Get_palavra()[k];
		break;
	case 3:
		for (int j = b; j < (b + c); j++)
			matriz[j][a] = lista[i].Get_palavra()[j - b];
		break;
	case 4:
		for (int j = b, k = 0; j > (b - c) and k < c; j--, k++)
			matriz[j][a] = lista[i].Get_palavra()[k];
		break;
	case 5:
		for (int j1 = a, j2 = b; j1 < (a + c) and j2 < (b + c); j1++, j2++)
			matriz[j2][j1] = lista[i].Get_palavra()[j1-a];
		break;
	case 6:
		for (int j1 = a, j2 = b, k = 0; j1 > (a - c) and j2 > (b - c) and k < c; j1--, j2--, k++)
			matriz[j2][j1] = lista[i].Get_palavra()[k];
		break;
	case 7:
		for (int j1 = a, j2 = b; j1 > (a - c) and j2 < (b + c); j1--, j2++)
			matriz[j2][j1] = lista[i].Get_palavra()[j2 - b];
		break;
	case 8:
		for (int j1 = a, j2 = b; j1 < (a + c) and j2 > (b - c); j1++, j2--)
			matriz[j2][j1] = lista[i].Get_palavra()[j1 - a];
		break;
	}
}
