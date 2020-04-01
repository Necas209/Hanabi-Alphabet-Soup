#pragma once
#include "Tabuleiro.h"
#include "Jogador.h"

class Jogo
{
private:
	Tabuleiro* tabuleiro;
	Jogador* jogador;
public:
	Jogo();
	virtual ~Jogo();
	void Set_tabuleiro(Tabuleiro* tab);
	void Set_jogador(Jogador* jog);
	Tabuleiro* Get_tabuleiro(void) const { return tabuleiro; };
	Jogador* Get_jogador(void) { return jogador; };
	void New_Jogo(void);
	void Run_Jogo(void);
};