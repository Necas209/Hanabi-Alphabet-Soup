#include<stdio.h>
#include<stdlib.h>

int main()
{
	FILE *file;
	file = fopen("Letras.txt", "r");
	
//	if(file == NULL)
//	{
//		printf("Nao foi possivel abrir o ficheiro.\n");
//		getchar();
//		exit(0);
//	}
	
	char frase[100];
	
	while(fgets(frase, 100, file) != NULL)
	{
		printf("%s", frase);
	}
	
	return(0);
}
