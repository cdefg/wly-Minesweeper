#ifndef __KRL__
#define __KRL__

//enum level{EASY, MID, HARD, USER};


typedef struct gridunit{
	int hasmine;
	int flagged;
	int mined;
	int minecount;
} GU, *pGU;

typedef struct grid{
	int height;
	int width;
	int mines;
	int cursor_x;
	int cursor_y;
	GU ** gu;
}GD, *pGD;

pGD initgrid(void);
void flag(pGD p, int x, int y);
void mine(pGD p, int x, int y, int depth);
int judge (pGD p);
void endgame(pGD p);

#endif
