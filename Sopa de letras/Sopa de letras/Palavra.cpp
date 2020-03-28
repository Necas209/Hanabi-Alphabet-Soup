#include "Palavra.h"

using namespace std;

Palavra::Palavra()
	:orientacao(-1), estado(false)
{
}

Palavra::Palavra(std::vector<Letra> palavra, Ponto ponto)
{
	this->palavra = palavra;
	ponto_inicial = ponto;
}

Palavra::~Palavra()
{
}

void Palavra::Set_Palavra(string str)
{
	int l = str.length();
	palavra.resize(l);
	for (int i = 0; i < l; i++)
	{
		palavra[i] = Letra(str[i], Ponto(), (int)str[i], Verify_letra(str[i]));
	}
}

int Palavra::Verify_letra(char c)
{
	return(c < 'a' or c > 'z');
}

void Palavra::RandOrientacao(void)
{
	int o;
	srand((unsigned)time(nullptr));
	o = rand() % 8 + 1;
	Set_orientacao(o);
}

void Palavra::RandPontoInicial(int x, int y)
{
	int n_x, n_y;
	srand((unsigned)time(nullptr));
	n_x = rand() % x;
	n_y = rand() % y;
	Set_ponto_inicial(Ponto(n_x, n_y));
}

void Palavra::operator=(Palavra p)
{
	Set_Palavra(p.Get_palavra());
	Set_orientacao(p.Get_orientacao());
	Set_estado(p.Get_estado());
	Set_ponto_inicial(p.Get_ponto_inicial());
}

string Palavra::Get_string()
{
	int l;
	l = Get_palavra().size();
	string aux;
	aux.resize(l);
	for (int i = 0; i < l; i++)
	{
		aux[i] = palavra[i].Get_letra();
	}
	return aux;
}

ostream& operator<<(ostream& os, Palavra p)
{
	os << p.Get_string();
	return os;
}
