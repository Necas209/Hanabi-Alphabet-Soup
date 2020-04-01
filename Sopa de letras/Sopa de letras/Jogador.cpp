#include "Jogador.h"
#include <string>

using namespace std;

Jogador::Jogador()
	:pontos(0)
{
	nome = Ask_nome();
	idade = Ask_idade();
}

Jogador::Jogador(string n, int id, int p)
	:nome(n), idade(id), pontos(p)
{
}

Jogador::~Jogador()
{
}

string Jogador::Ask_nome()
{
	string nome;
	cout << endl << "Insira o seu nome: ";
	cin.ignore();
	getline(cin, nome);
	return nome;
}

int Jogador::Ask_idade()
{
	int idade;
	cout << endl << "Insira a sua idade: ";
	cin >> idade;
	return idade;
}

ostream& operator<<(ostream& os, Jogador* jogador)
{
	os << endl << jogador->nome << endl << jogador->idade << endl;
	return os;
}
