/*
 * calibration.c
 *
 *  Created on: Mar 24, 2021
 *      Author: Altus
 */
#include "calibration.h"
#include "stm32f1xx_it.h"
UART_HandleTypeDef huart2;

uint8_t message[10] = "$1x______\n";

void calibration_sequence()
{
	HAL_UART_Transmit(&huart2, (uint8_t*)"$23252162\n", 10, 50);
for (int j = 0; j<8; j++)
  {
	message[2] = (j + 48);
	HAL_UART_Transmit(&huart2, (uint8_t*)message, 10, 50);
	set_LED_Column(j, 1);
	 HAL_Delay(1000);
	 set_LED_Column(j, 0);
 }

display[0][0]=1;
display[0][7]=1;
display[7][0]=1;
display[7][7]=1;
}

void wait_screen(){

//	for (int col; col<8;col++)
//	{
//		set_LED_Column(col, 0);
//	}
//
	for(int j=0; j<8;j++)
			{
			setColumn(j,0);
			setRow(j,0);
			}
	initialize_matrix();
	display[0][0]=1;
	display[0][7]=1;
	display[7][0]=1;
	display[7][7]=1;

}

