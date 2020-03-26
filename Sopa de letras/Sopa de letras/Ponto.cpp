#include "Ponto.h"

using namespace std;

Ponto::Ponto()
	:x(-1), y(-1)
{
}

Ponto::Ponto(int m_x, int m_y)
	:x(m_x), y(m_y)
{
}

Ponto::~Ponto()
{
}

bool Ponto::Set_x(int m_x)
{
	if (m_x < 0)
		return false;
	else
		x = m_x;
	return true;
}

bool Ponto::Set_y(int m_y)
{
	if (m_y < 0)
		return false;
	else
		y = m_y;
	return true;
}

void Ponto::Set_P(int m_x, int m_y)
{
	Set_x(m_x);
	Set_y(m_y);
}

void Ponto::Set_P(Ponto m_P)
{
	Set_x(m_P.Get_x());
	Set_y(m_P.Get_y());
}

bool Ponto::Ask2Set_P(void)
{
	int x, y;
	cout << "X: ";
	cin >> x;
	cout << "Y: ";
	cin >> y;
	Set_P(Ponto(x, y));
	return IsValid();
}

bool Ponto::IsValid(void)
{
	return (Get_x() >= 0 and Get_y()>=0);
}

void Ponto::ShowPonto(void)
{
	cout << "(x,y)" << '=' << '(' << x << ',' << y << ')';
}

bool Ponto::operator==(const Ponto ponto) const
{
	 return (x == ponto.Get_x()) ? (y == ponto.Get_y()) ? 1 : 0 : 0;
}

bool Ponto::operator!=(const Ponto ponto) const
{
	return (x == ponto.Get_x()) ? (y == ponto.Get_y()) ? 0 : 1 : 1;
}

void Ponto::operator=(Ponto ponto)
{
	Set_x(ponto.Get_x());
	Set_y(ponto.Get_y());
}
/*void Ponto::Save(ofstream& os)
{
	os << Get_x() << ' ' << Get_y();
}

void Ponto::Read(ifstream& is)
{
	int x, y;
	is >> x >> y;
	Set_P(Ponto(x, y));
}*/