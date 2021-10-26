///*
// * demo2game.c
// *
// *  Created on: Apr 15, 2021
// *      Author: Altus
// */
//
//#include "demo2game.h"
//
//ADC_HandleTypeDef hadc1;
//UART_HandleTypeDef huart2;
//volatile int8_t right_pressed=0;
//volatile int8_t left_pressed=0;
//volatile int8_t up_pressed=0;
//volatile int8_t down_pressed=0;
//volatile int8_t uart_transmit_ball_pos;
//int8_t xPos=4;
//int8_t yPos=4;
//extern int8_t xPrev;
//extern int8_t yPrev;
//int8_t xPrev=4;
//int8_t yPrev=4;
//uint8_t maze_message[10] = "$3xy_____\n";
//
//int sample_ADC()
//{
//	int sampled_value;
//	HAL_ADC_Start(&hadc1);
//	if(HAL_ADC_PollForConversion(&hadc1, 10))
//	{
//		sampled_value=HAL_ADC_GetValue(&hadc1);
//	}
//	HAL_ADC_Stop(&hadc1);
//	return sampled_value;
//}
//
//void start_game()
//{
//	display[0][0]=0;
//	display[0][7]=0;
//	display[7][0]=0;
//	display[7][7]=0;
//
//	yPrev=yPos;
//	xPrev=xPos;
//
//
//	if(right_pressed==1)
//	{
//		right_pressed=0;
//		if(xPos>=7){
//			xPos=xPos;
//		}else if (xPos<7)
//		{
//			xPos=xPos+1;
//		}
//	}
//
//	if(left_pressed==1)
//	{
//		left_pressed=0;
//		if(xPos<=0){
//			xPos=xPos;
//		}else if (xPos>0)
//		{
//			xPos=xPos-1;
//		}
//	}
//
//
//
//	if(uart_transmit_ball_pos==1)
//	{
//		int64_t sampled_value = 0;
//		HAL_ADC_Start(&hadc1);
//		HAL_ADC_PollForConversion(&hadc1, 10);
//
//		sampled_value = HAL_ADC_GetValue(&hadc1);
//
//		HAL_ADC_Stop(&hadc1);
//
//		//yPos=sample_ADC();
//		//uint8_t rawUART[10] = "xxxxxxxxx\n";
//		//rawUART[0]=(sampled_value-(sampled_value%1000))+48;
//		//yPos=(yPos*7)/4095;
//
//		yPos=(sampled_value*8/4095);
//		//rawUART[0]=yPos+48;
//
//		//HAL_UART_Transmit(&huart2, (uint8_t*)rawUART, 10, 50);
//		uart_transmit_ball_pos = 0;
//		maze_message[2] = (xPos + 48);
//		maze_message[3] = (yPos + 48);
//		HAL_UART_Transmit(&huart2, (uint8_t*)maze_message, 10, 50);
//	}
//
//	if((xPos!=xPrev)||(yPos!=yPrev))
//	{
//	display[yPrev][xPrev] = 0;
////	display[yPrev][xPrev-1]=0;
////	display[yPrev][xPrev+1]=0;
//	}
//	display[yPos][xPos] = 1;
//
//}

