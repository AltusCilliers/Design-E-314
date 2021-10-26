/*
 * tennisGame.h
 *
 *  Created on: May 4, 2021
 *      Author: Altus
 */

#ifndef INC_TENNISGAME_H_
#define INC_TENNISGAME_H_

#include "main.h"
#include "matrixDisplay.h"

void tennis_game();
void move_ball();
void tennis_gameStop();
void collision_detection();
void tennis_game();
void construct_tennis_game();

typedef struct {
    int8_t ballXpos;
    int8_t ballYpos;
    int8_t ballXprev;
    int8_t ballYprev;

    int8_t 	batXpos;
       int8_t batYpos1;
       int8_t batYpos2;
       int8_t batXprev;
       int8_t batYprev1;
       int8_t batYprev2;
} tballs;

#endif /* INC_TENNISGAME_H_ */
