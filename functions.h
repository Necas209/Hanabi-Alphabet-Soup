#include <stdlib.h>
#include <time.h>
#include "lab.h"

int PickPlayer (void) 
{
	srand(time(NULL));
	return rand()%2;
}
void Menu(int *option)
{
	setlocale(LC_ALL, "");
	puts("\n\n Menu:");
	puts("\n\t 1 - Jogar uma partida de Hanabi");
	puts("\n\t 2 - Carregar uma partida a partir de ficheiro");
	puts("\n\t 3 - Apresentar uma descrição do jogo na consola");
	puts("\n\t 4 - Sair da aplicação\n\n Opção: ");
	scanf("%d", option);
}
void PlayerName(char *name, int n)
{
	int i;
	printf("\n Digite o seu nome: ");
	for(i=0; i<n; i++)
		scanf("%c", &name[i]);
	
}
void PrintDeck(int dim)
{
	char d[]="Baralho:";
	showRectAt(100,15,9,6);
	printfAt(101,14,d);
	gotoxy(104,18);
	printf("%d", dim+1);
}
void PrintCL(int clues, int lifes)
{
	char pistas[]="Pistas: ";
	char vidas[]="Vidas: ";
	printfAt(85,15,pistas);
	printf("%d", clues);
	printfAt(85,20,vidas);
	printf("%d", lifes);
}
