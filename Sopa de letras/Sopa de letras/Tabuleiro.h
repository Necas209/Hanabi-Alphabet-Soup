#pragma once
#include "Letra.h"
#include "Palavra.h"

using namespace std;

class Tabuleiro
{
private:
	vector<vector<Letra>> matriz;
	vector<Palavra> lista;
	int DimX;
	int DimY;
	int n;          // numero de palavras
public:
	Tabuleiro();
	virtual ~Tabuleiro();
	void Set_matriz(vector<vector<Letra>> matriz) { this->matriz = matriz; };
	void Set_lista(vector<Palavra> lista) { this->lista = lista; };
	void Set_DimX(int DimX) { this->DimX = DimX; };
	void Set_DimY(int DimY) { this->DimY = DimY; };
	void Set_n(int n) { this->n = n; };
	vector<vector<Letra>> Get_matriz(void) const { return matriz; };
	vector<Palavra> Get_lista(void) const { return lista; };
	int Get_DimX(void) const { return DimX; };
	int Get_DimY(void) const { return DimY; };
	int Get_n(void) const { return n; };
	void Ask_DimX(void);
	void Ask_DimY(void);
	void Create_matriz(void);
	void Fill_matriz(void);
	void Show_matriz(void);
	void Load_lista(void);
	void Show_lista(void);
	bool CheckIfItFits(int i);
	bool CheckCrossing(int i);
	bool CheckLetter(int i, int x, int y, int k);
	void Insert_palavra(int i);
};