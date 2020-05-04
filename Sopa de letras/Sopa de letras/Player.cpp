#include "Player.h"

Player::Player()
	:score(0)
{
	Ask_name();
	Ask_age();
}

Player::~Player()
{
}

void Player::Ask_name()
{
	cout << endl << " Insira o seu nome: ";
	cin.ignore();
	getline(cin, name);
}

void Player::Ask_age()
{
	int age;
	cout << endl << " Insira a sua idade: ";
	cin >> age;
	if (!cin.good())
	{
		PreventLoop();
		Ask_age();
	}
	else
		this->age = age;
}

void Player::Increase_score(void)
{
	score++;
}

void Player::Show(void)
{
	cout << endl << " Nome: " << name << endl;
	cout << endl << " Idade: " << age << endl;
	cout << endl << " Pontuação: " << score << endl;
}

ostream& operator<<(ostream& os, Player& player)
{
	os << endl << " Nome: " << player.name << endl;
	os << endl << " Idade: " << player.age << endl;
	os << endl << " Pontuação: " << player.score << endl;
	return os;
}
