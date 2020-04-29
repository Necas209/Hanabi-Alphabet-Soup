#include "Point.h"

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
	x = m_x;
	y = m_y;
}

void Point::Set_P(Point m_P)
{
	x = m_P.x;
	y = m_P.y;
}

bool Point::Ask2Set_P(void)
{
	int x, y;
	cout << endl << " X: ";
	cin >> x;
	if (!cin.good())
	{
		PreventLoop();
		Ask2Set_P();
	}
	else {
		cout << endl << " Y: ";
		cin >> y;
		if (!cin.good())
		{
			PreventLoop();
			Ask2Set_P();
		}
		else
			Set_P(x, y);
	}
	return IsValid();
}

bool Point::IsValid(void)
{
	return (x >= 0 and y >= 0);
}

void Point::ShowPoint(void)
{
	cout << "(x,y)" << '=' << '(' << x << ',' << y << ')';
}

bool Point::operator==(const Point ponto) const
{
	 return (x == ponto.x) ? (y == ponto.y) ? 1 : 0 : 0;
}

bool Point::operator!=(const Point ponto) const
{
	return (x == ponto.x) ? (y == ponto.y) ? 0 : 1 : 1;
}

void Point::operator=(Point ponto)
{
	Set_P(ponto.x, ponto.y);
}
void Point::Save(ofstream& os)
{
	os << x << ' ' << y;
}

void Point::Read(ifstream& is)
{
	int x, y;
	is >> x >> y;
	Set_P(x,y);
}