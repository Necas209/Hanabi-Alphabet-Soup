#pragma once
#include "Board.h"
#include "Player.h"

class Game
{
private:
	Board* board;
	Player* player;
public:
	Game();
	virtual ~Game();
	void Set_board(Board* board) { this->board = board; };
	void Set_player(Player* player) { this->player = player; };
	Board* Get_board(void) const { return board; };
	Player* Get_player(void) const { return player; };
	void New_Game(void);
	void Run_Game(void);
	void Play(void);
};