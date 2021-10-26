/*
 * matrixDisplay.c
 *
 *  Created on: Apr 14, 2021
 *      Author: Altus
 */

#include "matrixDisplay.h"
#include "main.h"

int columnCounter=0;

void display_LED(int x, int y){
	setRow(x,1);
	setColumn(y,1);
}

void corner_display()
{
	display[0][0]=1;
	display[0][7]=1;
	display[7][0]=1;
	display[7][7]=1;
}

void initialize_matrix()
{
	for (int j = 0; j<8; j++)
	  {
		 for (int k = 0; k<8;k++)
		  {
			 display[j][k]=0;
		  }
	  }
}

void reset_matrix()
{
	for(int j=0; j<8;j++)
		{
		setColumn(j,0);
		setRow(j,0);
		}
}



//void display_matrix()
//{
//reset_matrix();
//setColumn(columnCounter,1);
//int8_t emptyLEDS = 0;
//	for(int row=0; row<8;row++)
//	{
//		if((display[row][columnCounter])!=0)
//		{
//			setRow(row,1);
//			//display_LED(row,columnCounter);
//		}else if ((display[row][columnCounter])==0)
//		{
//			//setRow(row,0);
//			emptyLEDS++;
//		}
//
//	}
//	if(emptyLEDS == 8)
//	{
//		setColumn(columnCounter,0);
//	}
//	if(columnCounter>=7)
//	{
//		columnCounter=0;
//	}else
//	{
//	columnCounter++;
//	}
//
//}

void display_matrix()
{
reset_matrix();
setRow(columnCounter,1);
int8_t emptyLEDS = 0;
	for(int row=0; row<8;row++)
	{
		if((display[columnCounter][row])!=0)
		{
			setColumn(row,1);
			//display_LED(row,columnCounter);
		}else if ((display[columnCounter][row])==0)
		{
			//setRow(row,0);
			emptyLEDS++;
		}

	}
	if(emptyLEDS == 8)
	{
		setRow(columnCounter,0);
	}
	if(columnCounter>=7)
	{
		columnCounter=0;
	}else
	{
	columnCounter++;
	}

}




void set_LED_Column(int x, int status)
{
	for (int row = 0; row < 8; row++) {
		display[row][x]=status;
	}
}

void set_LED_Row(int y, int status)
{
	for (int column = 0; column < 8; column++) {
		display[y][column]=status;
	}
}

void setColumn(int x, int y)
{
	switch(x)
	{
	case 0:
		HAL_GPIO_WritePin(GPIOB, COL0_Pin, y);
		break;

	case 1:
		HAL_GPIO_WritePin(GPIOB, COL1_Pin, y);
		break;

	case 2:
		HAL_GPIO_WritePin(GPIOB, COL2_Pin, y);
		break;

	case 3:
		HAL_GPIO_WritePin(GPIOB, COL3_Pin, y);
		break;

	case 4:
		HAL_GPIO_WritePin(GPIOA, COL4_Pin, y);
		break;

	case 5:
		HAL_GPIO_WritePin(GPIOA, COL5_Pin, y);
		break;

	case 6:
		HAL_GPIO_WritePin(GPIOA, COL6_Pin, y);
		break;

	case 7:
		HAL_GPIO_WritePin(GPIOC, COL7_Pin, y);
		break;
	}
}

void setRow(int x, int y)
{
	switch(x)
	{
	case 0:
		HAL_GPIO_WritePin(GPIOC, ROW0_Pin, y);
		break;

	case 1:
		HAL_GPIO_WritePin(GPIOC, ROW1_Pin, y);
		break;

	case 2:
		HAL_GPIO_WritePin(GPIOC, ROW2_Pin, y);
		break;

	case 3:
		HAL_GPIO_WritePin(GPIOA, ROW3_Pin, y);
		break;

	case 4:
		HAL_GPIO_WritePin(GPIOA, ROW4_Pin, y);
		break;

	case 5:
		HAL_GPIO_WritePin(GPIOB, ROW5_Pin, y);
		break;

	case 6:
		HAL_GPIO_WritePin(GPIOB, ROW6_Pin, y);
		break;

	case 7:
		HAL_GPIO_WritePin(GPIOB, ROW7_Pin, y);
		break;
	}
}

