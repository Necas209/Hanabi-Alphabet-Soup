#include "Game.h"

Game::Game()
{
	player = nullptr;
	board = nullptr;
}

Game::~Game()
{
	free(player);
	free(board);
}

void Game::Clear_Game(void)
{
	free(board);
	free(player);
}

void Game::Level_Menu(HWND hWnd)
{
	Level = CreateWindowA("STATIC", "Nível do jogador",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		400, 200, 150, 30,
		hWnd, nullptr, nullptr, nullptr);
	_Beginner = CreateWindowA("BUTTON", "Principiante",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		400, 300, 150, 30,
		hWnd, (HMENU)ID_BUTTON_BEGINNER, nullptr, nullptr);
	_Expert = CreateWindowA("BUTTON", "Experiente",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		400, 400, 150, 30,
		hWnd, (HMENU)ID_BUTTON_EXPERT, nullptr, nullptr);
}

void Game::Choose_Player(HWND hWnd, int ID)
{
	DestroyWindow(Level);
	DestroyWindow(_Beginner);
	DestroyWindow(_Expert);
	switch (ID)
	{
	case ID_BUTTON_BEGINNER:
		player = new Beginner(hWnd);
		break;
	case ID_BUTTON_EXPERT:
		player = new Expert(hWnd);
		break;
	}
}

void Game::New_Game(HWND hWnd)
{
	Level_Menu(hWnd);
}

void Game::Run_Game(HWND hWnd)
{
	board->Show_matrix(hWnd);
	/*while (player->Get_score() < board->Get_n_used())
	{
		system("CLS");
		board->Show_matrix();
		cout << endl << board->Get_n_used();
		Play(hWnd);
		cout << player;
		board->Show_list();
		this_thread::sleep_for(chrono::seconds(2));
	}
	cout << endl << " Ganhaste!!!" << endl;
	this_thread::sleep_for(chrono::seconds(2));
	system("ClS");*/
}

void Game::Play(HWND hWnd)
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
		Play(hWnd);
	}
}

void Game::Menu(HWND hWnd)
{
	NewGame = CreateWindowA("BUTTON", "Começar um novo jogo",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		400, 200, 200, 30,
		hWnd, (HMENU)ID_BUTTON_NEWGAME, nullptr, nullptr);
	LoadGame = CreateWindowA("BUTTON", "Carregar um jogo",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		400, 300, 200, 30,
		hWnd, (HMENU)ID_BUTTON_LOADGAME, nullptr, nullptr);
	Exit = CreateWindowA("BUTTON", "Sair",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		400, 400, 200, 30,
		hWnd, (HMENU)ID_BUTTON_EXIT, nullptr, nullptr);
}

void Game::Set_Player(HWND hWnd)
{
	player->Set_Player();
	board = new Board(hWnd);
}

void Game::Set_Board(HWND hWnd)
{
	board->Set_Board();
	board->Create_matrix();
	board->Load_list();
	board->Fill_matrix();
	Run_Game(hWnd);
}
