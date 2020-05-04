#pragma once
#include "Board.h"
#include "Beginner.h"
#include "Expert.h"

class Game
{
private:
	Board* board;
	Player* player;
public:
	Game();
	virtual ~Game();
	void Menu(void);
	void Choose_Player(void);
	void New_Game(void);
	void Run_Game(void);
	void Clear_Game(void);
	void Play(void);
};