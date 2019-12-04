#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "lab.h"
#include "interface.h"

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
void DealCards(void);
void PrintPlayerHand(char*);
void PrintBotHand(void);
void PrintBotCard(int);
void PrintFireworks(void);
void Display(void);
void PrintDiscardDeck(void);	

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
	int k=1;
	Start();
	int option=0;
	while (k==1) 
	{
	Menu(&option);
	system("cls");
	switch(option) {
		case 1:
		{
			dim = 49;
			char name[16];
			PlayerName(name,16);
			system("cls");
			InitializeDeck();
			ShuffleDeck();
			DealCards();
			PrintPlayerHand(name);
			PrintBotHand();
			PrintFireworks();
			PrintDiscardDeck();
			PrintCL(clues,lifes);
			PrintDeck(dim);
			PickPlayer();
			gotoxy(1,35);
			system("pause");
  			system("cls");
			break;
		}
		case 2:
		// iniciar um jogo guardado
		break;
		case 3:
		{
			FILE* rules=NULL;
			rules=fopen("rules.txt","r");
			char c;
			c = fgetc(rules);
    		while (c != EOF)
    		{
       			printf("%c", c);
        		c = fgetc(rules);
    		}
  			fclose(rules);
  			system("pause");
  			system("cls");
  			break;
  		}	
		case 4:
		{
			k=0;
			exit(0);
		}
		default:
			puts("\nA opção não existe.");
			system("pause");
  			system("cls");
			break;
	}
	}
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
	dim-=10;
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
			colour_id = 6;
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

void Display()
{
	int i = 0;
	for(i=0;i<=dim+10;i++){
    printf("%5s %-12s", deck[i].number, deck[i].colour);
    if(0==((i+1)%3))
    	printf("\n");
	}
}
