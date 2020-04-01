#include "Jogo.h"

Jogo::Jogo()
{
	jogador = nullptr;
	tabuleiro = nullptr;
}

Jogo::~Jogo()
{
}

void Jogo::Set_tabuleiro(Tabuleiro* tab)
{
	tabuleiro = tab;
}

void Jogo::Set_jogador(Jogador* jog)
{
	jogador = jog;
}

void Jogo::New_Jogo()
{
	jogador = new Jogador();
	tabuleiro = new Tabuleiro();
	tabuleiro->Create_matriz();
	tabuleiro->Load_lista();
	tabuleiro->Fill_matriz();
}

void Jogo::Run_Jogo()
{
	tabuleiro->Show_matriz();
	cout << jogador;
	tabuleiro->Show_lista();
}