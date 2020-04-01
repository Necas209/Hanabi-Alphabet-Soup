#include "Point.h"

using namespace std;

Point::Point()
	:x(-1), y(-1)
{
}

Point::Point(int m_x, int m_y)
	:x(m_x), y(m_y)
{
}

Point::~Point()
{
}

bool Point::Set_x(int m_x)
{
	if (m_x < 0)
		return false;
	else
		x = m_x;
	return true;
}

bool Point::Set_y(int m_y)
{
	if (m_y < 0)
		return false;
	else
		y = m_y;
	return true;
}

void Point::Set_P(int m_x, int m_y)
{
	Set_x(m_x);
	Set_y(m_y);
}

void Point::Set_P(Point m_P)
{
	Set_x(m_P.Get_x());
	Set_y(m_P.Get_y());
}

bool Point::Ask2Set_P(void)
{
	int x, y;
	cout << "X: ";
	cin >> x;
	cout << "Y: ";
	cin >> y;
	Set_P(Point(x, y));
	return IsValid();
}

bool Point::IsValid(void)
{
	return (Get_x() >= 0 and Get_y()>=0);
}

void Point::ShowPoint(void)
{
	cout << "(x,y)" << '=' << '(' << x << ',' << y << ')';
}

bool Point::operator==(const Point ponto) const
{
	 return (x == ponto.Get_x()) ? (y == ponto.Get_y()) ? 1 : 0 : 0;
}

bool Point::operator!=(const Point ponto) const
{
	return (x == ponto.Get_x()) ? (y == ponto.Get_y()) ? 0 : 1 : 1;
}

void Point::operator=(Point ponto)
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