#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <locale.h>
#include "lab.h"
#include "functions.h"

#define SIZE 10
#define MAX_COLOURS 5
#define MAX_NUMBERS 10
#define HAND 5

struct card {
    char *number;
    char colour[SIZE];
};
typedef struct card Deck;
char * numbers[MAX_NUMBERS] = {"1", "1", "1", "2", "2", "3", "3", "4", "4", "5"};
char colours[MAX_COLOURS][SIZE] = {"Amarelo", "Azul", "Verde", "Vermelho", "Branco"};

void InitializeDeck(void);
void ShuffleDeck(void);
void PlayerName(char *, int);
void DealCards(void);
void PrintPlayerHand(char*);
void PrintBotHand(void);
void PrintBotCard(int);
void PrintFireworks(void);
void Display(void);
void PrintDiscardDeck(void);	
void PrintCL(void);
void PrintDeck(void);
void Start(void);
void Menu(int *);

int dim=49;
int clues = 8;
int lifes = 3; 
int fireworks[5][5];
int discard_deck[5][5]={0};
Deck deck[50] = {"",""};
Deck player_hand[HAND];
Deck bot_hand[HAND];

void main() 
{
	Start();
	int option=0;
	Menu(&option);
	system("cls");
	switch(option) {
		case 1:
		{
			int play = PickPlayer();
			char name[16];
			PlayerName(name,16);
			system("cls");
			InitializeDeck();
			ShuffleDeck();
			DealCards();
			dim-=10;
			PrintPlayerHand(name);
			PrintBotHand();
			PrintFireworks();
			PrintDiscardDeck();
			PrintCL();
			PrintDeck();
			gotoxy(5,35);
			Display();
		}
		case 2:
			// Carregar uma partida a partir de um ficheiro
		case 3:
			// Apresentar uma descriçao do jogo na consola
		case 4:
			exit(0);
	}
	
}

void PlayerName(char *name, int n)
{
	int i;
	printf("\n Digite o seu nome: ");
	for(i=0; i<n; i++)
		scanf("%c", &name[i]);
	
}
void InitializeDeck()
{
  int i;
  for(i=0;i<dim+1;i++)
  {
		deck[i].number = numbers[i%MAX_NUMBERS];
    	strncpy(deck[i].colour, colours[i/MAX_NUMBERS], SIZE);
  }
}
void ShuffleDeck()
{
  int swapper = 0;
  int i, j;
  Deck temp = {"", ""};
  srand(time(NULL));
  for(j=0;j<5;j++)
  {
  	for(i=0;i<dim+1;i++)
 	{
		swapper = rand() % (dim+1); 
    	temp = deck[i];
    	deck[i] = deck[swapper];
    	deck[swapper] = temp;
    }
  }
}
void DealCards()
{
	int i;
	for(i=0;i<HAND;i++)
	{
		player_hand[i].number = deck[dim-2*i].number;
		strcpy(player_hand[i].colour, deck[dim-2*i].colour);
	}
	for(i=0;i<HAND;i++)
	{
		bot_hand[i].number = deck[dim-1-2*i].number;
		strcpy(bot_hand[i].colour, deck[dim-1-2*i].colour);
	}
}
void PrintPlayerHand(char *name)
{
	int k=0;
	gotoxy(3, 27);
	printf("%.8s", name);
	for (k=0; k<HAND; k++)
		showRectAt(10+14*k,25,8,6);
}
void PrintBotHand()
{
	int k=0;
	gotoxy(3, 8);
	puts("Bot");
	for (k=0; k<HAND; k++)
		PrintBotCard(k);
}
void PrintBotCard(int k)
{
	int i, colour_id;
	if(strcmp(bot_hand[k].colour, "Amarelo")==0)
			colour_id = 14;
	else if(strcmp(bot_hand[k].colour, "Azul")==0)
		 	colour_id = 11;
	else if(strcmp(bot_hand[k].colour, "Verde")==0)
			colour_id = 10;
	else if(strcmp(bot_hand[k].colour, "Vermelho")==0)
			colour_id = 4;
	else if(strcmp(bot_hand[k].colour, "Branco")==0)
			colour_id = 15;
	setColor(0,colour_id);
	showRectAt(10+14*k,5,8,6);
	for(i=1;i<4;i++)
	{
	setColor(colour_id,colour_id);
	showRectAt(10+14*k+i,5+i,8-2*i,6-2*i);
	}
	setColor(0,colour_id);
	printfAt(14+14*k,8,bot_hand[k].number);
	resetColor();
}
void PrintFireworks()
{
	int k=0;
	setForeColor(15);
	for(k=0; k<5; k++)
		showRectAt(11+14*k,16,6,4);
}
void PrintDiscardDeck()
{
	int i=0,j=0;
	for(i=0; i<MAX_COLOURS; i++)
	{
		printfAt(85,6+i,colours[i]);
		gotoxy(95+4*i,5);
		printf("%d", i+1);
		for(j=0; j<5; j++)
		{
		gotoxy(95+4*i,6+j);
		printf("%d", discard_deck[i][j]);
		}
	}
}
void PrintCL()
{
	char pistas[]="Pistas: ";
	char vidas[]="Vidas: ";
	printfAt(85,15,pistas);
	printf("%d", clues);
	printfAt(85,20,vidas);
	printf("%d", lifes);
}
void PrintDeck()
{
	char d[]="Baralho:";
	showRectAt(100,15,8,6);
	printfAt(100,14,d);
	gotoxy(103,18);
	printf("%d", dim+1);
}
void Display()
{
	int i = 0;
	for(i=0;i<=dim+10;i++){
    printf("%5s %-12s", deck[i].number, deck[i].colour);
    if(0==((i+1)%3))
    	printf("\n");
	}
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
	gotoxy(85,2);
	puts("Trabalho de:");
	gotoxy(85,4);
	puts("-Diogo Medeiros");
	gotoxy(85,5);
	puts("-Eduardo Chaves");
	gotoxy(85,6);
	puts("-João Rodrigues");
	sleep(3);
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
