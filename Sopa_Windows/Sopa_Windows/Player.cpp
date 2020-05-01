#include "Player.h"

Player::Player(HWND hWnd)
	:name(""), age(0), score(0)
{
	Player_Menu(hWnd);
}

Player::~Player()
{
}

void Player::Set_Player()
{
	name = p_name;
	age = n_age;
	DestroyWindow(_Player);
	DestroyWindow(_Name);
	DestroyWindow(Name_Input);
	DestroyWindow(_Age);
	DestroyWindow(Age_Input);
	DestroyWindow(Player_Button);
}

void Player::Player_Menu(HWND hWnd)
{
	_Player = CreateWindowA("STATIC", "Jogador",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		400, 200, 80, 30,
		hWnd, nullptr, nullptr, nullptr);
	_Name = CreateWindowA("STATIC", "Nome",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		300, 300, 100, 30,
		hWnd, nullptr, nullptr, nullptr);
	Name_Input = CreateWindowA("EDIT", "",
		WS_BORDER | WS_CHILD | WS_VISIBLE,
		400, 300, 200, 30,
		hWnd, (HMENU)ID_NAME, nullptr, nullptr);
	_Age = CreateWindowA("STATIC", "Idade",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		300, 400, 100, 30,
		hWnd, nullptr, nullptr, nullptr);
	Age_Input = CreateWindowA("EDIT", "",
		WS_BORDER | WS_CHILD | WS_VISIBLE,
		400, 400, 200, 30,
		hWnd, (HMENU)ID_NAME, nullptr, nullptr);
	Player_Button = CreateWindowA("BUTTON", "OK",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		420, 500, 50, 50,
		hWnd, (HMENU)ID_PLAYER_BUTTON, nullptr, nullptr);
}

void Player::Increase_score(void)
{
	score++;
}

ostream& operator<<(ostream& os, Player& player)
{
	os << endl << " Nome: " << player.name << endl;
	os << endl << " Idade: " << player.age << endl;
	os << endl << " Pontuação: " << player.score << endl;
	return os;
}

Beginner::Beginner(HWND hWnd)
	:Player(hWnd)
{
}

Expert::Expert(HWND hWnd)
	: Player(hWnd)
{
}
