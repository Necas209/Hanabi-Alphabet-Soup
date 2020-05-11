#include "Player.h"


Player::Player()
	:name(""), age(0), score(0)
{
}

Player::~Player()
{
}

void Player::New_player(void)
{
	Ask_name();
	Ask_age();
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
	cout << endl << " Pontua��o: " << score << endl;
}

void Player::Read(ifstream& is)
{
	string s;
	getline(is, s);
	is >> age >> score;
	getline(is, name, ';');
}

void Player::Save(ofstream& os)
{
	os << age << ' ' << score << ' ' << name << ';';
}

ostream& operator<<(ostream& os, Player& player)
{
	os << endl << " Nome: " << player.name << endl;
	os << endl << " Idade: " << player.age << endl;
	os << endl << " Pontua��o: " << player.score << endl;
	return os;
}
