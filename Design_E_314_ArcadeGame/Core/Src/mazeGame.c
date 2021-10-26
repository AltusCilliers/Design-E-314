/*
 * mazeGame.c
 *
 *  Created on: May 4, 2021
 *      Author: Altus
 */

#include "mazeGame.h"

int64_t maze_game_counter=0;
balls ball;

extern int16_t ax;
extern int16_t ay;
extern int16_t az;

uint8_t number_flag=0;
uint8_t maze_flag=0;
uint8_t mazemenuflag=0;
uint8_t IMU_Char=78;

volatile int8_t right_pressed;
volatile int8_t left_pressed;
volatile int8_t middle_pressed;
volatile int8_t up_pressed;
volatile int8_t down_pressed;

volatile int8_t end_toggle=1;
volatile int8_t player_toggle=1;
volatile int8_t uart_transmit_ball_pos=1;
volatile int8_t end_flicker=1;
volatile int8_t maze_ball_allowed_to_move=1;
extern volatile int64_t FlickerCounter;
volatile int8_t uart_transmit_tball_pos;
extern int8_t chooseMaze;


volatile int8_t ball_visible=1;
volatile int8_t goal_visible=1;

ADC_HandleTypeDef hadc1;
UART_HandleTypeDef huart2;
I2C_HandleTypeDef hi2c1;

uint8_t maze_message[10] = "$3xybg___\n";
int8_t togglebit = 0;
int8_t toggle = 1;
int8_t ptogglebit = 0;
int8_t ptoggle = 1;
int8_t end_visible=1;

uint8_t i2cMazeData[10];

//Constructor for maze game
void construct_maze_game(int8_t maze[8][8])
{

	ball_visible=1;
	goal_visible=1;
	player_toggle=1;
	end_toggle=1;
	end_visible=1;
	uart_transmit_ball_pos = 1;



	for (int col; col<8;col++)
	{
		set_LED_Column(col, 0);
	}

	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			display[row][col] = maze[row][col];
		}
	}


	ball.Xpos=0;
	ball.Ypos=0;
	ball.Xprev=0;
	ball.Yprev=0;

	display[ball.Xpos][ball.Ypos]=1;
}

void maze_game()
{
	if (maze_game_counter == 0)
	{
		if (number_flag==0)
		{
			display_maze_number(1); //displays maze1
			HAL_GPIO_WritePin(GPIOA, DEBUG1_Pin, 1);
			HAL_GPIO_WritePin(GPIOC, DEBUG2_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, DEBUG3_Pin, 0);
			HAL_GPIO_WritePin(GPIOB, DEBUG4_Pin, 0);
			number_flag=1;
		}
	}else if (maze_game_counter == 1)
	{
		if (number_flag==0)
		{
			display_maze_number(2); //displays maze1
			HAL_GPIO_WritePin(GPIOC, DEBUG2_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, DEBUG1_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, DEBUG3_Pin, 0);
			HAL_GPIO_WritePin(GPIOB, DEBUG4_Pin, 0);
			number_flag=1;
		}
	}else if (maze_game_counter == 2)
	{
		if (number_flag==0)
		{
			display_maze_number(3); //displays maze1
			HAL_GPIO_WritePin(GPIOA, DEBUG3_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, DEBUG1_Pin, 0);
			HAL_GPIO_WritePin(GPIOC, DEBUG2_Pin, 0);
			HAL_GPIO_WritePin(GPIOB, DEBUG4_Pin, 0);
			number_flag=1;
		}
	}else if (maze_game_counter == 3)
	{
		if (number_flag==0)
		{
			display_maze_number(4); //displays maze1
			HAL_GPIO_WritePin(GPIOB, DEBUG4_Pin, 1);
			HAL_GPIO_WritePin(GPIOA, DEBUG1_Pin, 0);
			HAL_GPIO_WritePin(GPIOC, DEBUG2_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, DEBUG3_Pin, 0);
			number_flag=1;

		}
	}


	if(maze_flag==0)//still in the maze menu
	{
		if(up_pressed==1)
		{
			up_pressed=0;
			number_flag=0;
			if(maze_game_counter<3)
			{
				maze_game_counter++;
			}
		}
		if (down_pressed==1)
		{
			down_pressed=0;
			number_flag=0;
			if(maze_game_counter>0)
			{
				maze_game_counter--;
			}
		}
		if(middle_pressed==1)
		{
			mazemenuflag=0;
			maze_flag = 1;
			switch(maze_game_counter)
			{
			case 0:
				construct_maze_game(maze1);
				break;
			case 1:
				construct_maze_game(maze2);
				break;
			case 2:
				construct_maze_game(maze3);
				break;
			case 3:
				construct_maze_game(maze4);
				break;
			}
			middle_pressed = 0;
			//construct_maze_game(maze_game_counter);
		}
	} else
	{

		//if(display[ball.Ypos][ball.Xpos]==5)//player reaches end
		switch(maze_game_counter)
		{
		case 0:
			if(maze1[ball.Ypos][ball.Xpos]==5)

			{
				middle_pressed=1;
				maze_gameStop();
			}
			break;
		case 1:
			if(maze2[ball.Ypos][ball.Xpos]==5)

			{
				middle_pressed=1;
				maze_gameStop();
			}
			break;
		case 2:
			if(maze3[ball.Ypos][ball.Xpos]==5)

			{
				middle_pressed=1;
				maze_gameStop();
			}
			break;
		case 3:
			if(maze4[ball.Ypos][ball.Xpos]==5)

			{
				middle_pressed=1;
				maze_gameStop();
			}
			break;
		}


		if(end_toggle==1)
		{



			goal_visible*=-1;
			toggle*=-1;
			togglebit=5;
			end_toggle=0;
			if(toggle==1)
			{
				togglebit = 0;
			}

			switch(maze_game_counter)
			{
			case 0:
				display[7][7]=togglebit;
				break;
			case 1:
				display[3][3]=togglebit;
				break;
			case 2:
				display[7][7]=togglebit;
				break;
			case 3:
				display[0][2]=togglebit;
				break;
			}

		}





		ball.Yprev=ball.Ypos;
		ball.Xprev=ball.Xpos;

		//below code is for I2C
		//	i2cMazeData[0]=0xA8; //set address to 0xA8 (X_Low address) + auto increment
		//	HAL_I2C_Master_Transmit(&hi2c1,0x32,i2cMazeData,1,10);
		//	HAL_I2C_Master_Receive(&hi2c1,0x32,i2cMazeData,6,10);

		//	ax = *((int16_t*)i2cMazeData);
		//	ay = *((int16_t*)(i2cMazeData+2));
		//	az = *((int16_t*)(i2cMazeData+4));

		if(ax>8192){ //sin30*16384, 16384 max positive raw value
			left_pressed=1;
			IMU_Char=76;
		}
		else if(ax<-8192){
			right_pressed=1;
			IMU_Char=82;
		}
		else if(ay>8192){
			down_pressed=1;
			IMU_Char=68;
		}
		else if(ay<-8192){
			up_pressed=1;
			IMU_Char=85;
		}else{
			IMU_Char=78;
//					down_pressed=0;
//					left_pressed=0;
//					right_pressed=0;
//					up_pressed=0;
		}



		if(maze_ball_allowed_to_move==1){
			maze_ball_allowed_to_move=0;
			if(right_pressed==1)
			{
				right_pressed=0;
				//line below is for collision detection
				if(display[ball.Ypos][ball.Xpos+1]!=1){
					if(ball.Xpos>=7){
						ball.Xpos=ball.Xpos;
					}else if (ball.Xpos<7)
					{
						ball.Xpos=ball.Xpos+1;
					}
				}

			}

			if(left_pressed==1)
			{
				left_pressed=0;
				//line below is for collision detection
				if(display[ball.Ypos][ball.Xpos-1]!=1){
					if(ball.Xpos<=0){
						ball.Xpos=ball.Xpos;
					}else if (ball.Xpos>0)
					{
						ball.Xpos=ball.Xpos-1;
					}
				}
			}

			if(up_pressed==1)
			{
				up_pressed=0;
				//line below is for collision detection
				if(display[ball.Ypos-1][ball.Xpos]!=1){
					if(ball.Ypos<=0){
						ball.Ypos=ball.Ypos;
					}else if (ball.Ypos>0)
					{
						ball.Ypos=ball.Ypos-1;
					}
				}
			}

			if(down_pressed==1)
			{
				down_pressed=0;
				//line below is for collision detection
				if(display[ball.Ypos+1][ball.Xpos]!=1){
					if(ball.Ypos>=7){
						ball.Ypos=ball.Ypos;
					}else if (ball.Ypos<7)
					{
						ball.Ypos=ball.Ypos+1;
					}
				}
			}
		}

		if((ball.Xpos!=ball.Xprev)||(ball.Ypos!=ball.Yprev))
		{
			display[ball.Yprev][ball.Xprev] = 0;
		}
		//display[ball.Ypos][ball.Xpos] = 1;





		if(uart_transmit_ball_pos==1)
		{
			uart_transmit_ball_pos = 0;
			maze_message[2] = (ball.Xpos + 48);
			maze_message[3] = (ball.Ypos + 48);
			maze_message[4] = (player_toggle + 48);
			maze_message[5] = (end_visible + 48);
			maze_message[6] = (IMU_Char);

			if(player_toggle==1){
				display[ball.Ypos][ball.Xpos]=1;
				player_toggle=0;
				end_visible=0;
			}
			else
			{
				display[ball.Ypos][ball.Xpos]=0;
				player_toggle=1;
				end_visible=1;
			}





			HAL_UART_Transmit(&huart2, (uint8_t*)maze_message, 10, 50);
		}

	}
}


void display_maze_number(int8_t n)
{

	switch(n)
	{
	case 1:
		for (int row = 0; row < 8; row++) {
			for (int col = 0; col < 8; col++) {
				display[row][col] = num1[row][col];
			}
		}
		break;
	case 2:
		for (int row = 0; row < 8; row++) {
			for (int col = 0; col < 8; col++) {
				display[row][col] = num2[row][col];
			}
		}
		break;
	case 3:
		for (int row = 0; row < 8; row++) {
			for (int col = 0; col < 8; col++) {
				display[row][col] = num3[row][col];
			}
		}
		break;
	case 4:
		for (int row = 0; row < 8; row++) {
			for (int col = 0; col < 8; col++) {
				display[row][col] = num4[row][col];
			}
		}
		break;
	}

}

void maze_gameStop()
{
	//middle_pressed=0;
	maze_game_counter=0;
	number_flag=0;
	maze_flag=0;
	mazemenuflag=0;
	ax=0;
	ay=0;

	HAL_GPIO_WritePin(GPIOA, DEBUG1_Pin, 0);
	HAL_GPIO_WritePin(GPIOC, DEBUG2_Pin, 0);
	HAL_GPIO_WritePin(GPIOA, DEBUG3_Pin, 0);
	HAL_GPIO_WritePin(GPIOB, DEBUG4_Pin, 0);

	//wait_screen();
}
