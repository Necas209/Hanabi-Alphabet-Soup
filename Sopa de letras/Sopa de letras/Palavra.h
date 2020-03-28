#pragma once
#include "Letra.h"
#include <vector>
#include <string>

using namespace std;

class Palavra
{
private:
	vector<Letra> palavra;
	int orientacao; // 1 - HF, 2 - HT, 3 - VB, 4 - VC, 5 - D1B, 6 - D1C, 7 - D2B, 8 - D2C
	bool estado;   // 0-por descobrir, 1-descoberto
	Ponto ponto_inicial;
public:
	Palavra();
	Palavra(vector<Letra> palavra, Ponto ponto);
	virtual ~Palavra();
	void Set_Palavra(string str);
	void Set_Palavra(vector<Letra> palavra) { this->palavra = palavra; };
	void Set_orientacao(int orientacao) { this->orientacao = orientacao; };
	void Set_estado(bool estado) { this->estado = estado; };
	void Set_ponto_inicial(Ponto ponto_inicial) { this->ponto_inicial = ponto_inicial; };
	vector<Letra> Get_palavra(void) const { return palavra; };
	int Get_orientacao(void) const { return orientacao; };
	bool Get_estado(void) const { return estado; };
	Ponto Get_ponto_inicial(void) const { return ponto_inicial; };
	string Get_string(void);
	int Verify_letra(char c);
	void RandOrientacao(void);
	void RandPontoInicial(int x, int y);
	void operator=(Palavra p);
	friend ostream& operator<<(ostream& os, Palavra p);
};

