#include "Jogo.h"

using namespace std;

int main() 
{
	int opção;
	Jogo jogo;
	setlocale(LC_ALL, "");
	cout << endl << "Diogo Medeiros n.o 70633" << endl;
	cout << endl << "\t\t\t\tSopa de letras" << endl;
	cout << endl << "\tMenu:" << endl;
	cout << endl << " 1 -> Começar um novo jogo" << endl;
	cout << endl << " 2 -> Salvar o jogo" << endl;
	cout << endl << " 3 -> Carregar um jogo" << endl;
	cout << endl << " 4 -> Sair" << endl;
	do
	{
		cout << endl << " Opção: ";
		cin >> opção;
		switch (opção)
		{
		case 1:
			jogo.Novo_Jogo();
			jogo.loop();
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			exit(0);
		default:
			cout << "Opção inválida.";
		}
	} while (opção < 1 or opção > 4);
}