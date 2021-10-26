/*
 * matrixDisplay.h
 *
 *  Created on: Apr 14, 2021
 *      Author: Altus
 */

#ifndef INC_MATRIXDISPLAY_H_
#define INC_MATRIXDISPLAY_H_

#include "main.h"

void initialize_matrix();
void reset_matrix();
void display_matrix();
void display_LED(int x, int y);
void setColumn(int x, int y);
void setRow(int x, int y);
void set_LED_Column(int x, int status);
void set_LED_Row(int x, int status);
void corner_display();
int8_t display[8][8];

#endif /* INC_MATRIXDISPLAY_H_ */

