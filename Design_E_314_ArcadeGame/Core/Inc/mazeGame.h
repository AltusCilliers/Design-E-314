/*
 * mazeGame.h
 *
 *  Created on: May 4, 2021
 *      Author: Altus Cilliers
 */

#ifndef INC_MAZEGAME_H_
#define INC_MAZEGAME_H_

#include "main.h"
#include "matrixDisplay.h"

void maze_game();
void maze_gameStop();
void display_maze_number(int8_t n);

typedef struct {
    int8_t Xpos;
    int8_t Ypos;
    int8_t Xprev;
    int8_t Yprev;
} balls;

//3==start & 5==end
int8_t maze1[8][8] = {
	{1, 0, 0, 0, 0, 0, 1, 0},
	{1, 1, 0, 1, 1, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 1, 0},
	{0, 1, 1, 1, 1, 1, 0, 1},
	{0, 0, 0, 0, 1, 0, 0, 0},
	{1, 1, 0, 1, 1, 0, 1, 0},
	{0, 0, 0, 1, 0, 0, 1, 0},
	{0, 1, 0, 0, 0, 1, 1, 5}
};

int8_t maze2[8][8] = {
	{1, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 1, 0, 1, 1, 0},
	{0, 0, 1, 0, 1, 0, 0, 0},
	{0, 1, 0, 5, 0, 0, 1, 1},
	{0, 0, 1, 1, 1, 1, 0, 0},
	{1, 0, 1, 0, 0, 1, 1, 0},
	{0, 0, 1, 0, 0, 0, 1, 0},
	{0, 0, 0, 0, 1, 0, 0, 0}
};

int8_t maze3[8][8] = {
	{1, 0, 0, 1, 1, 0, 0, 0},
	{0, 1, 0, 0, 1, 0, 1, 0},
	{0, 0, 1, 0, 1, 0, 1, 0},
	{1, 0, 1, 0, 0, 0, 1, 0},
	{0, 0, 1, 0, 1, 1, 1, 0},
	{0, 1, 0, 0, 1, 0, 0, 0},
	{0, 1, 0, 1, 1, 0, 1, 1},
	{0, 0, 0, 0, 1, 0, 0, 5}
};

int8_t maze4[8][8] = {
	{1, 1, 5, 1, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 1, 1, 0},
	{0, 1, 1, 1, 1, 0, 0, 0},
	{0, 1, 0, 0, 1, 0, 1, 0},
	{0, 1, 0, 1, 0, 0, 1, 0},
	{0, 0, 0, 0, 0, 1, 0, 0},
	{1, 1, 1, 1, 1, 1, 0, 1},
	{0, 0, 0, 0, 0, 0, 0, 0}
};


int8_t num1[8][8] = {
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0}
};

int8_t num2[8][8] = {
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 1, 0, 0, 0},
	{0, 0, 1, 0, 0, 1, 0, 0},
	{0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 1, 1, 1, 1, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0}
};

int8_t num3[8][8] = {
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 1, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 1, 1, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 1, 1, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0}
};

int8_t num4[8][8] = {
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 1, 0},
	{0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 1, 0, 1, 0, 0},
	{0, 0, 1, 1, 1, 1, 1, 0},
	{0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0}
};


#endif /* INC_MAZEGAME_H_ */