#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "lab.h"

int Random()
{
	int n;
	srand(time(NULL));
	n=rand()%2;
	return n;
}
void ClearScreen()
{
	int i=0, j=0;
	for(j=0; j<20; j++)
	{
		for(i=0; i<80; i++)
			showCharAt(1+i, 32+j, ' ');
	}
}
void Menu(int *option)
{
	setlocale(LC_ALL, "");
	puts("\n\n Menu:");
	puts("\n\t 1 - Jogar uma partida de Hanabi");
	puts("\n\t 2 - Carregar uma partida a partir de ficheiro");
	puts("\n\t 3 - Apresentar uma descrição do jogo na consola");
	puts("\n\t 4 - Sair da aplicação");
	printf("\n\n Opção: ");
	scanf("%d", option);
}
void PlayerName(char *name, int n)
{
	int i;
	printf("\n Digite o seu nome: ");
	for(i=0; i<n; i++)
		scanf("%c", &name[i]);
	
}
void PickPlayer(int *n)
{
	srand(time(NULL));
	*n=rand()%2;
	if(*n==1)
	{
		gotoxy(2,34);
		printf("O jogador e´ o primeiro a jogar.");
	}
	else
	{
		gotoxy(2,34);
		printf("O bot e´ o primeiro a jogar.");
	}
}
void PrintDeck(int dim)
{
	char d[]="Baralho:";
	showRectAt(100,15,9,6);
	printfAt(101,14,d);
	gotoxy(104,18);
	printf("%d", dim+1);
}
void Start()
{
	int i=0;
	char H1[]={186,186,204,186,186};
	char T[]={205,205,205,205};
	char H2[]={186,186,185,186,186};
	showVerticalWordAt(20,3,H1,5);	
	printfAt(21,5,T);
	showVerticalWordAt(25,3,H2,5);	
	char A1[]={201,186,204,186,186};
	char A2[]={187,186,185,186,186};
	showVerticalWordAt(30,3,A1,5);
	printfAt(31,3,T);
	printfAt(31,5,T);
	showVerticalWordAt(35,3,A2,5);
	char N1[]={201,186,186,186,186};
	char N2[]={186,186,186,186,188};
	showVerticalWordAt(40,3,N1,5);
	for(i=0;i<4;i++) {
		gotoxy(41+i,3+i);
		printf("\\");
	}
	showVerticalWordAt(45,3,N2,5);
	showVerticalWordAt(50,3,A1,5);
	printfAt(51,3,T);
	printfAt(51,5,T);
	showVerticalWordAt(55,3,A2,5);
	char B1[]={186,186,204,186,186};
	char B2[]={187,186,185,186,188};
	showVerticalWordAt(60,3,B1,5);
	for (i=3; i<=7;i+=2)
		printfAt(61,i,T);
	showVerticalWordAt(65,3,B2,5);
	char I1[]={205,205,203,205,205};
	char I2[]={205,205,202,205,205};
	char I3[]={186,186,186};
	printfAt(70,3,I1);
	printfAt(70,7,I2);
	showVerticalWordAt(72,4,I3,3);
	gotoxy(75,3);
	gotoxy(85,2);
	puts("Trabalho de:");
	gotoxy(85,4);
	puts("-Diogo Medeiros");
	gotoxy(85,5);
	puts("-Eduardo Chaves");
	gotoxy(85,6);
	puts("-João Rodrigues");
	sleep(2);
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

