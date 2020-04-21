#include "Game.h"
#include <thread>
#include <chrono>

Game::Game()
{
	player = nullptr;
	board = nullptr;
}

Game::~Game()
{
}

void Game::Choose_Player(void)
{
	int option;
	cout << endl << " Nível do jogador: " << endl;
	cout << endl << "\t1 -> Principiante" << endl;
	cout << endl << "\t2 -> Experiente" << endl;
	cout << endl << "\tOpção: ";
	cin >> option;
	if (!cin.good()) {
		cin.clear();
		string ignore;
		cin >> ignore;
		cout << endl << " Opção inválida." << endl;
		Choose_Player();
	}
	switch (option)
	{
	case 1:
		player = new Beginner();
		break;
	case 2:
		player = new Expert();
		break;
	default:
		cout << endl << " Opção inválida." << endl;
		Choose_Player();
	}
}

void Game::New_Game()
{
	Choose_Player();
	board = new Board();
	board->Create_matrix();
	board->Load_list();
	board->Fill_matrix();
}

void Game::Run_Game()
{
	do
	{
		system("CLS");
		board->Show_matrix();
		Play();
		cout << player;
		this_thread::sleep_for(chrono::seconds(2));
	} while (player->Get_score()<board->Get_n_used());
	board->Show_list();
}

void Game::Play(void)
{
	Word w;
	int option = 0;
	cout << endl << "\t1 -> Introduzir uma palavra" << endl;
	cout << endl << "\t2 -> Salvar o jogo" << endl;
	cout << endl << "\tOpção: ";
	cin >> option;
	switch (option)
	{
	case 1:
		w.Ask2Set_W();
		if (board->Check_If_Word_Is_Present(w))
		{
			cout << endl << "\tCerto!!" << endl;
			player->Increase_score();
		}
		break;
	case 2:
		break;
	default:
		cout << endl << "\t Opção inválida." << endl;
		Play();
	}
}
