#include "minesweeperui.h"
#include "minesweeperkrl.h"
#include <stdio.h>
#include <stdlib.h>

void printmine(pGD p){
	int i, j;
	printf("BASIC INFO:\n for debug use:\n");
	printf("height:%6d, width:%6d, mines:%6d\n", p->height, p->width, p->mines);
	for (i = 0; i < p->height; i++){
		for (j = 0; j < p->width; j++){
			printf("%2d", p->gu[i][j].hasmine);
		}
		printf("\n");
	}
}

void printinfo(pGD p){
	int i, j;
	printf("BASIC INFO:\n for debug use:\n");
	printf("height:%6d, width:%6d, mines:%6d\n", p->height, p->width, p->mines);
	for (i = 0; i < p->height; i++){
		for (j = 0; j < p->width; j++){
			char *printstr = (i == p->cursor_x && j == p->cursor_y)?">%d":"%2d";
			printf(printstr,  p->gu[i][j].minecount);
		}
		printf("\n");
	}
}

void printui(pGD p){
	int i, j;
	printf("height:%6d, width:%6d, mines:%6d\n", p->height, p->width, p->mines);
	for (i = 0; i < p->height; i++){
		for (j = 0; j < p->width; j++){
			if (i == p->cursor_x && j == p->cursor_y && p->gu[i][j].mined){
				printf(">\033[1;33;47m%d\033[0m", p->gu[i][j].minecount);
			}
			
			else if ((i != p->cursor_x || j != p->cursor_y )&& p->gu[i][j].mined){
				printf(" \033[1;33;47m%d\033[0m", p->gu[i][j].minecount);
			}
			else if ((i != p->cursor_x || j != p->cursor_y )&& p->gu[i][j].flagged){
				printf(" \033[1;31;47m!\033[0m");
			}
			else if (i == p->cursor_x && j == p->cursor_y && p->gu[i][j].flagged){
				printf(">\033[1;31;47m!\033[0m");
			}
			else if ((i != p->cursor_x || j != p->cursor_y )&& !p->gu[i][j].mined){
				printf(" ?");
			}
			else if(i == p->cursor_x && j == p->cursor_y && !p->gu[i][j].mined){
				printf(">?");
			}
			
		}
		printf("\n");
	}
}

