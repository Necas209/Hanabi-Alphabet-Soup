#pragma once
#include "Ponto.h"
#include <iostream>

using namespace std;

class Letra
{
private:
	char letra;
	int ascii;
	int M_m;    // 0 - minuscula, 1 - maiuscula
	Ponto ponto;
public:
	Letra();
	Letra(char letra, Ponto ponto, int ascii, int M_m);
	virtual ~Letra();
	void Set_letra(char letra) { this->letra = letra; };
	void Set_ascii(int ascii) { this->ascii = ascii; };
	void Set_M_m(int M_m) { this->M_m = M_m; };
	void Set_ponto(Ponto ponto) { this->ponto = ponto; };
	char Get_letra(void) const { return letra; };
	int Get_ascii(void) const { return ascii; };
	int Get_M_m(void) const { return M_m; };
	Ponto Get_ponto(void) const { return ponto; };
	void operator=(Letra l);
	friend ostream& operator<<(ostream& os, Letra l);
};

