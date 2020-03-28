#include "Letra.h"

Letra::Letra()
	:M_m(-1), ascii(0), letra(' ')
{
}

Letra::Letra(char letra, Ponto ponto, int ascii, int M_m)
{
	this->ponto = ponto;
	this->letra = letra;
	this->ascii = ascii;
	this->M_m = M_m;
}

Letra::~Letra()
{
}

void Letra::Set_Letra(char letra, int ascii, int M_m, Ponto ponto)
{
	Set_letra(letra);
	Set_ascii(ascii);
	Set_M_m(M_m);
	Set_ponto(ponto);
}

void Letra::RandLetra(int x, int y)
{
	char c;
	srand((unsigned)time(nullptr));
	c = rand() % 26 + 65;
	Set_Letra(c, c, 1, Ponto(x, y));
}

void Letra::operator=(Letra l)
{
	Set_letra(l.Get_letra());
	Set_ascii(l.Get_ascii());
	Set_M_m(l.Get_M_m());
	Set_ponto(l.Get_ponto());
}

ostream& operator<<(ostream& os, Letra l)
{
	os << l.letra;
	return os;
}
