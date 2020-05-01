#pragma once
#include "Board.h"
#include "Player.h"

HWND NewGame, LoadGame, Exit;
HWND Level, _Beginner, _Expert;

class Game
{
private:
	Board* board;
	Player* player;
public:
	Game();
	virtual ~Game();
	void Clear_Game(void);
	void Level_Menu(HWND hWnd);
	void Menu(HWND hWnd);
	void Set_Player(HWND hWnd);
	void Set_Board(HWND hWnd);
	void Choose_Player(HWND hWnd, int ID);
	void New_Game(HWND hWnd);
	void Run_Game(HWND hWnd);
	void Play(HWND hWnd);
};