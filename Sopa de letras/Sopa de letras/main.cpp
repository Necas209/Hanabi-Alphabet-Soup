#include "Game.h"
#include <locale>

using namespace std;

int main() 
{
	int option;
	Game game;
	setlocale(LC_ALL, "portuguese");
	cout << endl << " Diogo Medeiros n.o 70633" << endl;
	cout << endl << "\t\t\t\tSopa de letras" << endl << endl;
	cout << endl << "\tMenu:" << endl;
	cout << endl << " 1 -> Começar um novo jogo" << endl;
	cout << endl << " 2 -> Salvar o jogo" << endl;
	cout << endl << " 3 -> Carregar um jogo" << endl;
	cout << endl << " 4 -> Sair" << endl;
	do
	{
		cout << endl << " Opção: ";
		cin >> option;
		if (!cin.good()) {
			cin.clear();
			string ignore;
			cin >> ignore;
			cout << endl << "Opção inválida." << endl;
		}
		else {
			switch (option)
			{
			case 1:
				game.New_Game();
				game.Run_Game();
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				exit(0);
			default:
				cout << " Opção inválida.";
			}
		}
	} while (option < 1 or option > 4);
}