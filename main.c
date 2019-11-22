#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define SIZE 10
#define MAX 50
#define MAX_COLOURS 5
#define MAX_NUMBERS 10

struct card {
    char *number;
    char colour[SIZE];
};
typedef struct card Deck;

char * numbers[MAX_NUMBERS] = {"1", "1", "1", "2", "2", "3", "3", "4", "4", "5"};
char colours[MAX_COLOURS][SIZE] = {"Amarelo", "Azul", "Verde", "Vermelho", "Branco"};

void InitializeDeck(Deck[]);
void ShuffleDeck(Deck[]);
void DisplayDeck(const Deck[]);
void PlayerName(char *, int);
void DealCards(Deck[], Deck player_hand[], Deck bot_hand[]);
int PickPlayer (int *);
void main() 
{
	int option;
	puts("\n Menu:");
	puts("\n\t 1 - Jogar uma partida de Hanabi");
	puts("\n\t 2 - Carregar uma partida a partir de ficheiro");
	puts("\n\t 3 - Apresentar uma descricao do jogo na consola");
	puts("\n\t 4 - Sair da aplicacao\n\n Opcao: ");
	scanf("%d", &option);
	system("cls");
	switch(option) {
		case 1:
		{
			Deck deck[MAX] = {"",""};
			Deck player_hand[5];
			Deck bot_hand[5];
			char name[16];
			
			PlayerName(name,16);
			InitializeDeck(deck);
			ShuffleDeck(deck);
    		DisplayDeck(deck);
			puts("\n\n\n");
			DealCards(deck, player_hand, bot_hand);
			int play = PickPlayer(&play);
			int clues = 8, lifes = 3;
		}
		case 2:
			// Carregar uma partida a partir de um ficheiro
		case 3:
			// Apresentar uma descriçao do jogo na consola
		case 4:
			exit(0);	
	}
	
}
int PickPlayer (int *play) 
{
	srand(time(NULL));
	*play = rand()%2;
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
  int i = 0;
  Deck temp = {"", ""};
  srand(time(NULL));
  for(i=0;i<MAX;i++)
  {
		swapper = rand() % MAX; 
    	temp = deck[i];
    	deck[i] = deck[swapper];
    	deck[swapper] = temp;
  }
}

void DisplayDeck(const Deck deck[])
{
	int i = 0;
  	for(i=0;i<MAX;i++)
	{
    	printf("%5s %-10s", deck[i].number, deck[i].colour);
    	if(0==((i+1)%3))
		{
      		printf("\n");
    	}
	}
}

void DealCards(Deck deck[], Deck player_hand[], Deck bot_hand[])
{
	int i;
	for(i=0;i<5;i++)
	{
		player_hand[i].number = deck[MAX-1-2*i].number;
		strcpy(player_hand[i].colour, deck[MAX-1-2*i].colour);
		//printf("%5s %-12s", player_hand[i].number, player_hand[i].colour);
	}
	for(i=0;i<5;i++)
	{
		bot_hand[i].number = deck[MAX-2-2*i].number;
		strcpy(bot_hand[i].colour, deck[MAX-2-2*i].colour);
		//printf("%5s %-12s", bot_hand[i].number, bot_hand[i].colour);
	}
}
