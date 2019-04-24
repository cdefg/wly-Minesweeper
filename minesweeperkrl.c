#include <stdio.h>
#include <stdlib.h>
#include "minesweeperkrl.h"
#include "randomgen.h"

int mines  = 10;
int height = 10;
int width  = 10;

pGD initgrid(void){
	pGD p = (pGD) malloc(sizeof(GD));
	p->height = height;
	p->width  = width;
	p->mines  = mines;
	p->cursor_x = p->height/2;
	p->cursor_y = p->width/2;
	p->gu = (pGU *) malloc(sizeof(pGU)*height);
	int i, j;
	for (i = 0; i < width; i++){
		p->gu[i] = (pGU) malloc(sizeof(GU)*width);
	}

	int laying_mines = mines;
	int tar_x, tar_y;
	startrandom();
	while(laying_mines > 0){
		tar_x = rangerandom(p->height);
		tar_y = rangerandom(p->width );
		printf("tar_x:%d tar_y:%d\n", tar_x, tar_y);
		if (p->gu[tar_x][tar_y].hasmine == 0){
			p->gu[tar_x][tar_y].hasmine = 1;
			laying_mines--;
		}
	}
	
	for (i = 0; i < p->height; i++){
		for (j = 0; j < p->width; j++){
			p->gu[i][j].flagged = 0;
			p->gu[i][j].mined   = 0;
			char *printstr = (i == p->cursor_x && j == p->cursor_y)?">%d":"%2d";
			if (i == 0 && j == 0){
				p->gu[i][j].minecount = p->gu[0][1].hasmine 
					+p->gu[1][0].hasmine
					+p->gu[1][1].hasmine;
			}
			else if (i == 0 && j == p->width-1){
				p->gu[i][j].minecount = p->gu[0][j-1].hasmine
					+p->gu[1][j-1].hasmine
					+p->gu[1][j].hasmine;
			}
			else if (i == p->height-1 && j == 0){
				p->gu[i][j].minecount = p->gu[i-1][0].hasmine
					+p->gu[i-1][1].hasmine
					+p->gu[i][1].hasmine;
			}
			else if (i == p->height-1 && j == p->width-1){
				p->gu[i][j].minecount = p->gu[i-1][j].hasmine
					+p->gu[j-1][i].hasmine
					+p->gu[i-1][j-1].hasmine;
			}
			else if (i == 0 && (j != 0|| j != p->width-1)){
				p->gu[i][j].minecount = p->gu[0][j-1].hasmine
					+p->gu[0][j+1].hasmine
					+p->gu[1][j-1].hasmine
					+p->gu[1][j+1].hasmine
					+p->gu[1][j].hasmine;
			}
			else if (i == p->height-1 && (j != 0|| j != p->width-1)){
				p->gu[i][j].minecount = p->gu[i][j-1].hasmine
					+p->gu[i][j+1].hasmine
					+p->gu[i-1][j-1].hasmine
					+p->gu[i-1][j].hasmine
					+p->gu[i-1][j+1].hasmine;
			}
			else if (j == 0 && (i != 0 || i != p->height-1)){
				p->gu[i][j].minecount = p->gu[i-1][j].hasmine
					+p->gu[i+1][j].hasmine
					+p->gu[i-1][j+1].hasmine
					+p->gu[i][j+1].hasmine
					+p->gu[i+1][j+1].hasmine;
			}
			else if (j == p->width-1 && (i != 0 || i != p->height-1)){
				p->gu[i][j].minecount = p->gu[i-1][j].hasmine
					+p->gu[i+1][j].hasmine
					+p->gu[i-1][j-1].hasmine
					+p->gu[i][j-1].hasmine
					+p->gu[i+1][j-1].hasmine;
			}
			else{
				p->gu[i][j].minecount = p->gu[i-1][j-1].hasmine
					+p->gu[i-1][j].hasmine
					+p->gu[i-1][j+1].hasmine
					+p->gu[i][j-1].hasmine
					+p->gu[i][j+1].hasmine
					+p->gu[i+1][j-1].hasmine
					+p->gu[i+1][j].hasmine
					+p->gu[i+1][j+1].hasmine;
			}
		}
	}
	
	return p;
}

void flag(pGD p, int x, int y){
	if (p->gu[x][y].flagged){
		p->mines++;
	}
	else 
		p->mines--;
	p->gu[x][y].flagged ^= 1;
}

//recursive structure
void mine(pGD p, int x, int y, int depth){
	if (p->gu[x][y].flagged == 1){
		return;
	}
	p->gu[x][y].mined = 1;
	if (depth == 1){
		if (x > 0){
			if (  p->gu[x-1][y].hasmine == 0 && p->gu[x-1][y].mined == 0 && p->gu[x-1][y].minecount == 0){
				mine(p, x-1, y, 1);
			}
			else if (  p->gu[x-1][y].hasmine == 0 && p->gu[x-1][y].mined == 0 && p->gu[x-1][y].minecount != 0){
				mine(p, x-1, y, 0);
			}
		}
		if (y > 0){
			if (  p->gu[x][y-1].hasmine == 0 && p->gu[x][y-1].mined == 0 && p->gu[x][y-1].minecount == 0){
				mine(p, x, y-1, 1);
			}
			else if (  p->gu[x][y-1].hasmine == 0 && p->gu[x][y-1].mined == 0 && p->gu[x][y-1].minecount != 0){
				mine(p, x, y-1, 0);
			}
		}
		if (x < p->height-1){
			if (  p->gu[x+1][y].hasmine == 0 && p->gu[x+1][y].mined == 0 && p->gu[x+1][y].minecount == 0){
				mine(p, x+1, y, 1);
			}
			else if (  p->gu[x+1][y].hasmine == 0 && p->gu[x+1][y].mined == 0 && p->gu[x+1][y].minecount != 0){
				mine(p, x+1, y, 0);
			}
		}
		if (y < p->width-1){
			if (  p->gu[x][y+1].hasmine == 0 && p->gu[x][y+1].mined == 0 && p->gu[x][y+1].minecount == 0){
				mine(p, x, y+1, 1);
			}
			else if (  p->gu[x][y+1].hasmine == 0 && p->gu[x][y+1].mined == 0 && p->gu[x][y+1].minecount != 0){
				mine(p, x, y+1, 0);
			}
		}
	}
}

int judge (pGD p){
	if (p->mines == 0){
		return 2;//2 for success
	}
	int i, j;
	for (i = 0; i < p->height; i++){
		for (j = 0; j < p->width; j++){
			if (p->gu[i][j].mined == 1 && p->gu[i][j].hasmine == 1){
				return 1;//1 for failure
			}
		}
	}

	return 0; //0 to continue
}

void endgame(pGD p){
	int i;
	for (i = 0; i < p->height; i++){
		free(p->gu[i]);
	}
	free(p->gu);
	free(p);
}
