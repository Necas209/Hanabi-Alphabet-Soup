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
		this_thread::sleep_for(chrono::seconds(2));
	} while (player->Get_score()<board->Get_n());
	board->Show_list();
}

void Game::Play(void)
{
	string w;
	Point p;
	int option = 0;
	while (option != 1 and option != 2)
	{
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
			p.Ask2Set_P();

			if (board->Check_If_Word_Is_Present(w, p))
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
		}
	}
}
