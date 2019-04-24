#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int startrandom(void){
	srand(time(NULL));
} 
int rangerandom(int max){
	return rand()%max;
}
