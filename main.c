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
#define NAME 16

struct card {
    int number;
    char colour[SIZE];
};
typedef struct card Deck;
int numbers[MAX_NUMBERS] = {1,1,1,2,2,3,3,4,4,5};
char colours[MAX_COLOURS][SIZE] = {"Amarelo", "Azul", "Verde", "Vermelho", "Branco"}; /* 0, 1, 2, 3, 4 */

struct clue {
	int nc[5];
	int cc[5];
};
typedef struct clue Clues;

int CardColour(Deck arr[], int);
int ColourID(Deck arr[], int);
void InitializeDeck(void);
void ShuffleDeck(void);
void DealCards(void);
void PrintPlayerHand(char*);
void PrintBotHand(void);
void PrintFireworks(void);
void Display(void);
void PrintDiscardDeck(void);
void PlayerTurn(void);
void PlayerDiscard(void);
void PlayerPlay(void);
void PlayerClues(void);

char name[NAME]="";
int turn;
int dim=49;
int clues = 8;
int lifes = 3; 
int fireworks[5]={0};
int discard_deck[5][5]={0};
Deck deck[50];
Deck player_hand[HAND];
Deck bot_hand[HAND];
Clues player_clues={{0},{0}};
Clues bot_clues={{0},{0}};

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
			clues=8;
			lifes=3;
			PlayerName(name,NAME);
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
			PickPlayer(&turn);
			system("pause");
			ClearScreen();
			Display();
			PlayerTurn();
			Display();
			gotoxy(1,50);
			system("pause");
			ClearScreen();
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
void PlayerTurn()
{
	int jog;
	gotoxy(2,34);
	puts("\tA sua jogada:");
	puts("\n\t 1. Dar uma pista");
	if(clues<=7)
		puts("\n\t 2. Descartar uma carta");
	puts("\n\t 3. Jogar uma carta");
	if(turn==1)
		puts("\n\t 4. Gravar o jogo e sair");
	printf("\n\t Opção: ");
	scanf("%d", &jog);
	ClearScreen();
	switch(jog) {
		case 1:
			PlayerClues();
			break;
		case 2:
		{
			PlayerDiscard();
			break;
		}
		case 3:
			PlayerPlay();
			break;
		case 4:
		//	SaveGame();
			break;	
	}
}
void PlayerClues()
{
	ClearScreen();
	char option, clue_col[10]="";
	int i, col, num;
	gotoxy(2,34);
	printf("Escolha o  tipo de pista que pretende dar:\n\n\t- Cor (C)\n\n\t- Número (N)\n\n  Opção: ");
	scanf(" %c", &option);
	switch(option)
	{
		case 'c': case 'C':	
			printf("\n  Escolha a cor:");
			printf("\n\n\t- Amarelo (1)\n\n\t- Azul (2)\n\n\t- Verde (3)\n\n\t- Vermelho (4)\n\n\t- Branco (5)\n\n  Opção: ");
			scanf(" %d", &col);
			switch(col) {
				case 1:
				strcpy(clue_col, "Amarelo");
				break;
				case 2:
				strcpy(clue_col, "Azul");
				break;
				case 3:
				strcpy(clue_col, "Verde");
				break;	
				case 4:
				strcpy(clue_col, "Vermelho");
				break;
				case 5:					
				strcpy(clue_col, "Branco");
				break;
				default:
				printf("\n  Cor inválida.");
				sleep(1);
				PlayerClues();
				break;
			}
			for(i=0; i<HAND; i++)
			{
				if(strcmp(bot_hand[i].colour, clue_col)==0)
					bot_clues.cc[i]=1;
			}
			break;
		case 'n': case 'N':
			printf("\n  Escolha o número (1-5): ");
			scanf(" %d", &num);
			if(num<1||num>5)
			{
				printf("\n  Número inválido.");
				sleep(1);
				PlayerClues();
			}
			else
			{
				for(i=0; i<HAND; i++)
				{
					if(bot_hand[i].number==num)
					bot_clues.nc[i]=1;
				}
			}
			break;
		default:
			printf("\n\n  Opção inválida.");
			sleep(1);
			PlayerClues();
			break;
	}
}
void PlayerPlay()
{
	int i, col;
	gotoxy(2,34);
	printf("Escolha de 1 a 5 a carta que pretende jogar: ");
	scanf("%d", &i);
	i--;
	printf("\n Jogaste a carta %d %s.", player_hand[i].number, player_hand[i].colour);
	col=ColourID(player_hand, i);
	if(player_hand[i].number==(fireworks[col]+1))
	{
		fireworks[col]++;
		PrintFireworks();
	}
	else
	{
		printf("\n A carta que jogaste não é válida!");
		discard_deck[player_hand[i].number-1][col]++;
		PrintDiscardDeck();
		lifes--;
	}
	player_hand[i].number=deck[dim].number;
	strcpy(player_hand[i].colour, deck[dim].colour);
	player_clues.nc[i]=0;
	player_clues.cc[i]=0;
	PrintPlayerHand(name);
	dim--;
	PrintDeck(dim);
}
void PlayerDiscard()
{
	int i, c, num;
		gotoxy(2,34);
		printf("Escolha de 1 a 5 a carta que pretende descartar: ");
		scanf("%d", &i);
		i--;
		printf("\n Descartaste a carta %d %s.", player_hand[i].number, player_hand[i].colour);
		c=ColourID(player_hand, i);
		num=player_hand[i].number-1;
		discard_deck[num][c]++;
		PrintDiscardDeck();
		player_hand[i].number=deck[dim].number;
		strcpy(player_hand[i].colour, deck[dim].colour);
		player_clues.nc[i]=0;
		player_clues.cc[i]=0;
		PrintPlayerHand(name);
		dim--;
		PrintDeck(dim);
}
int ColourID(Deck arr[], int k)
{
	if(strcmp(arr[k].colour, "Amarelo")==0)
			return 0;
	else if(strcmp(arr[k].colour, "Azul")==0)
		 	return 1;
	else if(strcmp(arr[k].colour, "Verde")==0)
			return 2;
	else if(strcmp(arr[k].colour, "Vermelho")==0)
			return 3;
	else if(strcmp(arr[k].colour, "Branco")==0)
			return 4;
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
  Deck temp;
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
	int k=0, i=0, cardcolour;
	for(k=0; k<NAME; k++)
		showCharAt(80+k,28,name[k]);
	for (k=0; k<HAND; k++) {
		cardcolour=CardColour(player_hand,k);
		if(player_clues.cc[k]==1) {
			setColor(0,cardcolour);
			showRectAt(10+14*k,25,8,6);
			for(i=1; i<4; i++) {
				setColor(cardcolour,cardcolour);
				showRectAt(10+14*k+i,25+i,8-2*i,6-2*i);
			}	
		}
		else
		{
			resetColor();
			showRectAt(10+14*k,25,8,6);
		}
		if(player_clues.nc[k]==1 && player_clues.cc[k]==1)
		{
			setColor(0,cardcolour);
			showNumAt(14+14*k,28,bot_hand[k].number);
		}
		else if(player_clues.nc[k]==1 && player_clues.cc[k]==0)
			showNumAt(14+14*k,28,bot_hand[k].number);
	}
	resetColor();
}
void PrintBotHand()
{
	int k=0, i=0, cardcolour;
	gotoxy(3, 8);
	puts("Bot");
	for (k=0; k<HAND; k++)
	{
	cardcolour=CardColour(bot_hand,k);
	setColor(0,cardcolour);
	showRectAt(10+14*k,5,8,6);
	for(i=1;i<4;i++)
	{
	setColor(cardcolour,cardcolour);
	showRectAt(10+14*k+i,5+i,8-2*i,6-2*i);
	}
	setColor(0,cardcolour);
	showNumAt(14+14*k,8,bot_hand[k].number);
	resetColor();
	}
}
void PrintFireworks()
{
	int k=0;
	for(k=0; k<5; k++)
	{
		switch(k)
		{
			case 0:
				setForeColor(6);
				break;
			case 1:
				setForeColor(11);
				break;
			case 2:
				setForeColor(10);
				break;
			case 3:
				setForeColor(4);
				break;
			case 4:
				setForeColor(15);
				break;
		}
		showRectAt(11+14*k,16,6,4);
		gotoxy(14+14*k,18);
		printf("%d", fireworks[k]);
		resetColor();
	}
}
void PrintDiscardDeck()
{
	int i=0,j=0;
	for(i=0; i<MAX_COLOURS; i++)
	{	
		if(strcmp(colours[i], "Amarelo")==0)
			setForeColor(6);
	else if(strcmp(colours[i], "Azul")==0)
		 	setForeColor(11);
	else if(strcmp(colours[i], "Verde")==0)
			setForeColor(10);
	else if(strcmp(colours[i], "Vermelho")==0)
			setForeColor(4);
	else if(strcmp(colours[i], "Branco")==0)
			setForeColor(15);
		printfAt(85,6+i,colours[i]);
		resetColor();
		gotoxy(96+4*i,5);
		printf("%d", i+1);
		for(j=0; j<5; j++)
		{
		gotoxy(96+4*i,6+j);
		printf("%d", discard_deck[i][j]);
		}
	}
}
int CardColour(Deck arr[], int k)
{
	if(strcmp(arr[k].colour, "Amarelo")==0)
			return 6;
	else if(strcmp(arr[k].colour, "Azul")==0)
		 	return 11;
	else if(strcmp(arr[k].colour, "Verde")==0)
			return 10;
	else if(strcmp(arr[k].colour, "Vermelho")==0)
			return 4;
	else if(strcmp(arr[k].colour, "Branco")==0)
			return 15;
}
void Display()
{
	int i = 0;
	gotoxy(1,60);
	for(i=0;i<=49;i++){
    printf("%d %s", deck[i].number, deck[i].colour);
    if(0==((i+1)%3))
    	printf("\n");
	}
	for(i=0; i<HAND; i++)
	{
		printf("\n\n\t%d %s", player_hand[i].number, player_hand[i].colour);
	}
	for(i=0; i<HAND; i++)
		printf("\n\n\t %d %d", player_clues.nc[i], player_clues.cc[i]);
}
