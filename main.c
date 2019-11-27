#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <locale.h>
#include "lab.h"

#define SIZE 10
#define MAX 50
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

void InitializeDeck(Deck[]);
void ShuffleDeck(Deck[]);
void PlayerName(char *, int);
void DealCards(Deck[], Deck player_hand[], Deck bot_hand[]);
void PrintPlayerHand(Deck player_hand[], char name[]);
void PrintPlayerCard(Deck player_hand[], int);
void PrintBotHand(Deck bot_hand[]);
void PrintBotCard(Deck bot_hand[], int );
int PickPlayer (void);
void PrintFireworks(void);
void Display(const Deck deck[]);
void PrintDiscardDeck(int discard_deck[][5]);

void main() 
{
	setlocale(LC_ALL, "");
	int option;
	puts("\n Menu:");
	puts("\n\t 1 - Jogar uma partida de Hanabi");
	puts("\n\t 2 - Carregar uma partida a partir de ficheiro");
	puts("\n\t 3 - Apresentar uma descrição do jogo na consola");
	puts("\n\t 4 - Sair da aplicação\n\n Opção: ");
	scanf("%d", &option);
	system("cls");
	switch(option) {
		case 1:
		{
			Deck deck[MAX] = {"",""};
			Deck player_hand[HAND];
			Deck bot_hand[HAND];
			int play = PickPlayer();
			int clues = 8, lifes = 3; 
			int discard_deck[5][5];
			int fireworks[5][5];
			char name[16];
			PlayerName(name,16);
			system("cls");
			InitializeDeck(deck);
			ShuffleDeck(deck);
			DealCards(deck, player_hand, bot_hand);
			PrintPlayerHand(player_hand, name);
			PrintBotHand(bot_hand);
			PrintFireworks();
			PrintDiscardDeck(discard_deck);
			gotoxy(5,35);
		}
		case 2:
			// Carregar uma partida a partir de um ficheiro
		case 3:
			// Apresentar uma descriçao do jogo na consola
		case 4:
			exit(0);
	}
	
}
int PickPlayer (void) 
{
	srand(time(NULL));
	int n=rand()%2;
	return n;
}
void PlayerName(char *name, int n)
{
	int i;
	printf("\n Digite o seu nome: ");
	for(i=0; i<n; i++)
		scanf("%c", &name[i]);
	
}
void InitializeDeck(Deck deck[])
{
  int i;
  for(i=0;i<MAX;i++)
  {
		deck[i].number = numbers[i%MAX_NUMBERS];
    	strncpy(deck[i].colour, colours[i/MAX_NUMBERS], SIZE);
  }
}
void ShuffleDeck(Deck deck[])
{
  int swapper = 0;
  int i, j;
  Deck temp = {"", ""};
  srand(time(NULL));
  for(j=0;j<5;j++)
  {
  	for(i=0;i<MAX;i++)
 	{
		swapper = rand() % MAX; 
    	temp = deck[i];
    	deck[i] = deck[swapper];
    	deck[swapper] = temp;
    }
  }
}
void DealCards(Deck deck[], Deck player_hand[], Deck bot_hand[])
{
	int i;
	for(i=0;i<HAND;i++)
	{
		player_hand[i].number = deck[MAX-1-2*i].number;
		strcpy(player_hand[i].colour, deck[MAX-1-2*i].colour);
	}
	for(i=0;i<HAND;i++)
	{
		bot_hand[i].number = deck[MAX-2-2*i].number;
		strcpy(bot_hand[i].colour, deck[MAX-2-2*i].colour);
	}
}
void PrintPlayerHand(Deck player_hand[], char *name)
{
	int k=0;
	gotoxy(3, 27);
	printf("%.8s", name);
	for (k=0; k<HAND; k++)
		PrintPlayerCard(player_hand, k);
}
void PrintPlayerCard(Deck player_hand[], int k)
{
	showRectAt(10+14*k,25,8,6);
}
void PrintBotHand(Deck bot_hand[])
{
	int k=0;
	gotoxy(3, 8);
	puts("Bot");
	for (k=0; k<HAND; k++)
		PrintBotCard(bot_hand, k);
}
void PrintBotCard(Deck bot_hand[], int k)
{
	int colour_id;
	if(strcmp(bot_hand[k].colour, "Amarelo")==0)
			colour_id = 14;
	else if(strcmp(bot_hand[k].colour, "Azul")==0)
		 	colour_id = 11;
	else if(strcmp(bot_hand[k].colour, "Verde")==0)
			colour_id = 10;
	else if(strcmp(bot_hand[k].colour, "Vermelho")==0)
			colour_id = 12;
	else if(strcmp(bot_hand[k].colour, "Branco")==0)
			colour_id = 15;
	setForeColor(colour_id);
	showRectAt(10+14*k,5,8,6);
	printfAt(14+14*k,8,bot_hand[k].number);
}
void PrintFireworks(void)
{
	int k=0;
	setForeColor(15);
	for(k=0; k<5; k++)
		showRectAt(11+14*k,16,6,4);
}
void PrintDiscardDeck(int discard_deck[][5])
{
	int i=0, j=0;
	for(i=0; i<MAX_COLOURS; i++)
	{
		for(j=0; j<5; j++)
			discard_deck[i][j]=0;
	}
	for(i=0; i<MAX_COLOURS; i++)
	{
		printfAt(85,6+i,colours[i]);
		gotoxy(95+3*i,5);
		printf("%d", i+1);
		for(j=0; j<5; j++)
		{
		gotoxy(95+3*i,6+j);
		printf("%d", discard_deck[i][j]);
		}
	}
}
void Display(const Deck deck[]){
  int i = 0;
  for(i=0;i<MAX;i++){
    printf("%5s of %-12s", deck[i].number, deck[i].colour);
    if(0==((i+1)%3)){
      printf("\n");
    }
  }
}
