#pragma once
#include <iostream>

using namespace std;

class Jogador
{
private:
	string nome;
	int idade;
	int pontos;
public:
	Jogador();
	Jogador(string n, int id, int p);
	virtual ~Jogador();
	void Set_nome(string nome) { this->nome = nome; };
	void Set_idade(int idade) { this->idade = idade; };
	void Set_pontos(int pontos) { this->pontos = pontos; };
	string Get_nome(void) const { return nome; };
	int Get_idade(void) const { return idade; };
	int Get_pontos(void) const { return pontos; };
	string Ask_nome();
	int Ask_idade();
	friend ostream& operator<<(ostream& os, Jogador* jogador);
};

class Principiante :
	public Jogador
{

};

class Experiente :
	public Jogador
{

};