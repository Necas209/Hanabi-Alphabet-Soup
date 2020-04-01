#include "Player.h"
#include <string>

using namespace std;

Player::Player()
	:score(0), name(Ask_name()), age(Ask_age())
{
}

Player::Player(string n, int id, int p)
	:name(n), age(id), score(p)
{
}

Player::~Player()
{
}

string Player::Ask_name()
{
	string name;
	cout << endl << "Insira o seu nome: ";
	cin.ignore();
	getline(cin, name);
	return name;
}

int Player::Ask_age()
{
	int age;
	cout << endl << "Insira a sua idade: ";
	cin >> age;
	return age;
}

void Player::Increase_score(void)
{
	score++;
}

ostream& operator<<(ostream& os, Player* player)
{
	os << endl << "Nome: " << player->name << endl;
	os << endl << "Idade: " << player->age << endl;
	os << endl << "Pontuação: " << player->score << endl;
	return os;
}
