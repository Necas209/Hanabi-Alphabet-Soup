#ifndef _LABH_		//protectes from multiple including...
#define _LABH_		//... needs an #endif at bottom

#include "functions.h"

//changes both foreground and background colors
void setColor(int foreGround, int backGround) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backGround * 16 + foreGround);
}
//changes foreground color while keeping background color
void setForeColor(int foreGround) {
	int backGround = MY_COLOR_BLACK;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	backGround = csbiInfo.wAttributes / 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backGround * 16 + foreGround);
}
//changes background color while keeping foreground color
void setBackColor(int backGround) {
	int foreGround = MY_COLOR_BLACK;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	foreGround = csbiInfo.wAttributes % 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backGround * 16 + foreGround);
}
//Colors reset: foreground white, background black
void resetColor() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), MY_COLOR_BLACK * 16 + MY_COLOR_WHITE);
}

//allows to place the cursor at any given position
void gotoxy(int x, int y) {
	COORD c = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
//allows to draw a rectangle (double lines) at any given position
void showRectAt(int x, int y, int width, int height) {

	setlocale(LC_ALL, "C");
	gotoxy(x, y);
	cout << (char)201;
	for (int i = 1; i < width; i++) {
		cout << (char)205;
	}

	cout << (char)187;
	gotoxy(x, height + y);
	cout << (char)200;

	for (int i = 1; i < width; i++) {
		cout << (char)205;
	}

	cout <<(char)188;

	for (int i = y + 1; i < height + y; i++) {
		gotoxy(x, i);
		cout << (char)186;

		gotoxy(x + width, i);
		cout << (char)186;

	}
	setlocale(LC_ALL, "");
}
//allows to draw a rectangle (double lines) at any given position, rotated by 90º 
void show90RectAt(int x, int y, int width, int height) {
	showRectAt(x, y, height * 2, width / 2);
}
//show a char at a designated position
void showCharAt(int x, int y, char c) {
	setlocale(LC_ALL, "C");
	gotoxy(x, y);
	cout << c;
	setlocale(LC_ALL, "");
}
//write a 'string' verticaly at a designated position
void showVerticalWordAt(int x, int y, string s) {
	setlocale(LC_ALL, "C");
	int i = 0;
	for (i = 0; i < s.length(); i++) {
		gotoxy(x, y + i);
		cout << s[i];
	}

	setlocale(LC_ALL, "");
}
//write an horizontal 'string' at a designated position
void printfAt(int x, int y, string s) {
	setlocale(LC_ALL, "");
	gotoxy(x, y);
	cout << s;
	setlocale(LC_ALL, "");
}
///////////////////////////////////////////////////////////////
void PreventLoop(void)
{
	cin.clear();
	string ignore;
	cin >> ignore;
	cout << endl << "Opção inválida." << endl;
}

void Upper(string& s)
{
	transform(s.begin(), s.end(), s.begin(), ::toupper);
}
#endif