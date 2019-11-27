#include <stdlib.h>
#include <time.h>
#include "lab.h"

int PickPlayer (void) 
{
	srand(time(NULL));
	return rand()%2;
}

