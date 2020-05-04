#include "Game.h"

Game::Game()
{
	player = nullptr;
	board = nullptr;
}

Game::~Game()
{
	delete player;
	delete board;
}

void Game::Menu(void)
{
	int option;
	setlocale(LC_ALL, "");
	cout << endl << " Diogo Medeiros n.o 70633" << endl;
	cout << endl << "\t\t\t\tSopa de letras" << endl << endl;
	cout << endl << "\tMenu:" << endl;
	cout << endl << " 1 -> Começar um novo jogo" << endl;
	cout << endl << " 2 -> Salvar o jogo" << endl;
	cout << endl << " 3 -> Carregar um jogo" << endl;
	cout << endl << " 4 -> Sair" << endl;
	cout << endl << " Opção: ";
	cin >> option;
	if (!cin.good()) 
		PreventLoop();
	else {
		switch (option)
		{
			case 1:
				New_Game();
				Run_Game();
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				exit(0);
			default:
				cout << " Opção inválida.";
				system("cls");
				Menu();
		}
	}
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
		PreventLoop();
		Choose_Player();
	}
	switch (option)
	{
	case 1:
		player = new Beginner;
		break;
	case 2:
		player = new Expert;
		break;
	default:
		cout << endl << " Opção inválida." << endl;
		Choose_Player();
	}
}

void Game::New_Game()
{
	system("cls");
	Choose_Player();
	system("cls");
	board = new Board;
	board->Create_matrix();
	board->Load_list();
	board->Fill_matrix();
}

void Game::Run_Game()
{
	while (player->Get_score() < board->Get_n_used())
	{
		system("CLS");
		board->Show_matrix();
		cout << endl << board->Get_n_used();
		Play();
		player->Show();
		board->Show_list();
		this_thread::sleep_for(chrono::seconds(3));
	}
	cout << endl << " Ganhaste!!!" << endl;
	this_thread::sleep_for(chrono::seconds(5));
	system("ClS");
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
