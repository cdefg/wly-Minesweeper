#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "minesweeperkrl.h"
#include "minesweeperui.h"

int main(int argc, char *argv[]) {
	pGD grid = initgrid();
	//printmine(grid);
	
	//printf("cx:%d cy:%d\n", grid->cursor_x, grid->cursor_y);
	int isfail = 0;
	char ch;

	initscr();
	printui(grid);
	cbreak();
	while((ch = getch()) != 27){
		endwin();
		if (ch == 'w' || ch == 'W'){
			if (grid->cursor_x > 0){
				grid->cursor_x--;
			}
		}
		else if (ch == 's' || ch == 'S'){
			if (grid->cursor_x < grid->width - 1){
				grid->cursor_x++;
			}
		} 
		else if (ch == 'a' || ch == 'A'){
			if (grid->cursor_y > 0){
				grid->cursor_y--;
			}
		}
		else if (ch == 'd' || ch == 'D'){
			if (grid->cursor_y < grid->height - 1){
				grid->cursor_y++;
			}
		}
		else if (ch == ' '){
			flag(grid, grid->cursor_x, grid->cursor_y);
		}
		else if (ch == 'm'){
			mine(grid, grid->cursor_x, grid->cursor_y, 1);
		}
		printf("\f");
		printui(grid);
		isfail = judge(grid);
		if (isfail)
			break;
		initscr();
		cbreak();
	}
	endwin();
	
	if (isfail == 1){
		printf("\nYou lost, a pity!\n");
	}
	else if (isfail == 2) {
		printf("\nYou win,  congratulations.\n");
	}
	

	endgame(grid);

	printf("\f");
	printf("Happy next time!\n");
	return 0;
}
