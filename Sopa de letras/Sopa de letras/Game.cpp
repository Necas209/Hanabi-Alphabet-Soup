#include "Game.h"

Game::Game()
{
	player = nullptr;
	board = nullptr;
}

Game::~Game()
{
}

void Game::New_Game()
{
	player = new Player();
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
		system("pause");
	} while (player->Get_score()<board->Get_n());
	board->Show_list();
}

void Game::Play(void)
{
	string w;
	int option;
	cout << endl << "\t1 -> Introduzir uma palavra" << endl;
	cout << endl << "\t2 -> Salvar o jogo" << endl;
	cout << endl << "\tOpção: ";
	cin >> option;
	switch (option)
	{
	case 1:
		cout << endl << "Palavra: ";
		cin.ignore();
		getline(cin, w);
		if (board->Check_If_Word_Is_Present(w))
		{
			cout << endl << "\tCerto!!" << endl;
			player->Increase_score();
		}	
		else
			cout << endl << "\tA palavra não existe na matriz.";
		break;
	case 2:
		break;
	default:
		cout << endl << "\t Opção inválida." << endl;
		Play();
	}
}
