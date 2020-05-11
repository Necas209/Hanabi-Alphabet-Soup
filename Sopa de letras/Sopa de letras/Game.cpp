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
	cout << endl << " 1 -> Come�ar um novo jogo" << endl;
	cout << endl << " 2 -> Salvar o jogo" << endl;
	cout << endl << " 3 -> Carregar um jogo" << endl;
	cout << endl << " 4 -> Sair" << endl;
	cout << endl << " Op��o: ";
	cin >> option;
	if (!cin.good()) 
		PreventLoop();
	else {
		switch (option)
		{
			case 1:
				New_Game();
				Run_Game();
				Clear_Game();
				break;
			case 2:
				Save_Game();
				break;
			case 3:
				Load_Game();
				break;
			case 4:
				exit(0);
			default:
				cout << " Op��o inv�lida.";
				system("cls");
				Menu();
		}
	}
}

void Game::Choose_Player(void)
{
	int option;
	cout << endl << " N�vel do jogador: " << endl;
	cout << endl << "\t1 -> Principiante" << endl;
	cout << endl << "\t2 -> Experiente" << endl;
	cout << endl << "\tOp��o: ";
	cin >> option;
	if (!cin.good()) {
		PreventLoop();
		Choose_Player();
	}
	else
	{
		switch (option)
		{
		case 1:
			player = new Beginner;
			break;
		case 2:
			player = new Expert;
			break;
		default:
			cout << endl << " Op��o inv�lida." << endl;
			Choose_Player();
		}
		player->New_player();
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
		board->Show_list();
		Play();
		player->Show();
		this_thread::sleep_for(chrono::seconds(3));
	}
	cout << endl << " Ganhaste!!!" << endl;
	this_thread::sleep_for(chrono::seconds(5));
	system("ClS");
}

void Game::Save_Game(void)
{
	Beginner* B;
	Expert* E;
	ofstream save;
	save.open("save.txt");
	if (!save)
		cout << endl << "Erro ao abrir o ficheiro." << endl;
	else
	{
		player->Save(save);
		save << "\n";
		board->Save(save);
	}
	save.close();
}

void Game::Load_Game(void)
{
}

void Game::Clear_Game(void)
{
	board->Clear_Board();
	delete board;
	delete player;
}

void Game::Play(void)
{
	Word w;
	int option = 0;
	int l = board->Get_DimY() + 2;
	for (int i = l; i < l + 20; i++)
	{
		for (int j = 1; j < 30; j++)
		{
			showCharAt(j, i, ' ');
		}
	}
	gotoxy(1, l);
	cout << endl << "\t1 -> Introduzir uma palavra" << endl;
	cout << endl << "\t2 -> Salvar o jogo" << endl;
	cout << endl << "\tOp��o: ";
	cin >> option;
	if (!cin.good())
		PreventLoop();
	else
	{
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
			Save_Game();
			break;
		default:
			cout << endl << "\t Op��o inv�lida." << endl;
		}
	}
}
