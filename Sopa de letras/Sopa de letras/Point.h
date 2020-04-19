#pragma once
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

class Point
{
private:
	int x;
	int y;
public:
	Point();
	Point(int m_x, int m_y);
	virtual ~Point();
	bool Set_x(int m_x);
	bool Set_y(int m_y);
	void Set_P(int m_x, int m_y);
	void Set_P(Point m_P);
	bool Ask2Set_P(void);
	int Get_x(void) const { return x; }
	int Get_y(void) const { return y; }
	bool IsValid(void);
	void ShowPoint(void);
	bool operator==(const Point ponto) const;
	bool operator!=(const Point ponto) const;
	void operator=(Point ponto);
	void Save(ofstream& os);
	void Read(ifstream& is);
};

