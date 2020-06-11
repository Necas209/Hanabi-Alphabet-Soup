#include "Game.h"

Game::Game()
	:player(nullptr), board(nullptr)
{
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
	cout << endl << " 2 -> Carregar um jogo" << endl;
	cout << endl << " 3 -> Sair" << endl;
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
				Load_Game();
				break;
			case 3:
				exit(0);
			default:
				cout << " Opção inválida.";
				system("cls");
				Menu();
		}
	}
}

void Game::Choose_Level(void)
{
	int option;
	cout << endl << " Nível do jogador: " << endl;
	cout << endl << "\t1 -> Principiante" << endl;
	cout << endl << "\t2 -> Experiente" << endl;
	cout << endl << "\tOpção: ";
	cin >> option;
	if (!cin.good() or (option != 1 and option != 2)) {
		PreventLoop();
		Choose_Level();
	}
	else
	{
		switch (option)
		{
		case 1:
			player = new Beginner;
			board = new Easy_Board;
			break;
		case 2:
			player = new Expert;
			board = new Hard_Board;
			break;
		}
		player->Ask_name();
		player->Ask_age();
	}
}

void Game::New_Game()
{
	system("cls");
	Choose_Level();
	system("cls");
	board->Create_matrix();
	board->Load_list();
	board->Fill_matrix();
}

void Game::Run_Game()
{
	auto start = chrono::high_resolution_clock::now();
	while (board->Number_NOT_FOUND() > 0)
	{
		system("CLS");
		board->Show_matrix();
		board->Show_list();
		Play(start);
		player->Show();
		this_thread::sleep_for(chrono::seconds(3));
	}
	cout << endl << " Ganhaste!!!" << endl;
	Clear_Game();
	this_thread::sleep_for(chrono::seconds(5));
	system("CLS");
}

void Game::Save_Game(void)
{
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
	char c;
	string s;
	ifstream load;
	load.open("save.txt");
	if(!load)
		cout << endl << "Erro ao abrir o ficheiro." << endl;
	else
	{
		load >> c;
		if (c == 'B')
			player = new Beginner;
		else
			player = new Expert;
		load >> c;
		player->Read(load);
		getline(load, s);
		load >> c;
		if (c == 'E')
			board = new Easy_Board;
		else
			board = new Hard_Board;
		board->Read(load);
		Run_Game();
	}
	load.close();
}

void Game::Clear_Game(void)
{
	delete player;
	delete board;
}

void Game::Play(chrono::time_point<chrono::high_resolution_clock> start)
{
	Word w;
	bool flag;
	chrono::time_point<chrono::high_resolution_clock> end;
	int option = 0;
	double max_time;
	chrono::duration<double> elapsed;
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
	cout << endl << "\tOpção: ";
	cin >> option;
	if (!cin.good())
		PreventLoop();
	else
	{
		switch (option)
		{
		case 1:
			w.Ask2Set_W();
			end = chrono::high_resolution_clock::now();
			elapsed = end - start;
			cout << elapsed.count();
			flag = board->Check_If_Word_Is_Present(w);
			if (flag)
				cout << endl << "\tCerto!!" << endl;
			max_time = double(board->Get_DimX() * board->Get_DimY()) / 4;
			player->Score(flag, elapsed, max_time);
			break;
		case 2:
			Save_Game();
			break;
		default:
			cout << endl << "\t Opção inválida." << endl;
		}
	}
}
