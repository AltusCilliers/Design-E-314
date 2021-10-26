/*
 * tennisGame.c
 *
 *  Created on: May 4, 2021
 *      Author: Altus
 */

#include "tennisGame.h"

int64_t tennis_game_counter=0;
tballs tball;

ADC_HandleTypeDef hadc1;
UART_HandleTypeDef huart2;

extern int16_t ax;
extern int16_t ay;

uint8_t IMU_CharT=78;
volatile int64_t TennisSysTickCounter;
volatile int8_t ball_move=0;
volatile int8_t bat_move=0;
volatile int8_t uart_transmit_tball_pos;
volatile int8_t middle_pressed;
volatile int8_t right_pressed;
volatile int8_t left_pressed;
volatile int8_t up_pressed;
volatile int8_t down_pressed;


int8_t ball_angle=0;
int16_t Number_Of_Bounces=0;
int16_t ball_velocity=700;
int16_t speed=0;

uint8_t tennis_message[10] = "$2xyvdxy_\n";

void construct_tennis_game()
{
	TennisSysTickCounter = 0;
	ball_angle=0;
	speed=0;
	Number_Of_Bounces=0;
	ball_velocity=700;
	uart_transmit_tball_pos = 0;
	for (int col; col<8;col++)
	{
		set_LED_Column(col, 0);
	}

	tball.batXpos=0;
	tball.batYpos1=4;
	tball.batYpos2=5;
	tball.ballXpos=7;
	tball.ballYpos=4;
	tball.ballXprev=7;
	tball.ballYprev=4;
	display[0][0]=0;
	display[0][7]=0;
	display[7][0]=0;
	display[7][7]=0;


}


void tennis_game()
{
	if (tennis_game_counter == 0)
	{
		construct_tennis_game();
		tennis_game_counter++;
	} else
	{
		tennis_game_counter++;
	}


	if(Number_Of_Bounces/3 < 10)
	{
		ball_velocity = 700 - (Number_Of_Bounces/3)*50;
		speed=(700-ball_velocity)/50;
	}

	if(TennisSysTickCounter >= ball_velocity){
		TennisSysTickCounter=0;
		collision_detection();
		move_ball();
	}


	if((tball.ballXpos!=tball.ballXprev)||(tball.ballYpos!=tball.ballYprev))
	{
		display[tball.ballYprev][tball.ballXprev] = 0;
	}
	if((tball.batXpos!=tball.batXprev)||(tball.batYpos1!=tball.batYprev1))
	{
		display[tball.batYprev1][tball.batXprev] = 0;
		display[tball.batYprev2][tball.batXprev] = 0;
	}

	tball.ballXprev=tball.ballXpos;
	tball.ballYprev=tball.ballYpos;

	tball.batXprev=tball.batXpos;
	tball.batYprev1=tball.batYpos1;
	tball.batYprev2=tball.batYpos2;


	if(ax>8192){ //sin30*16384, 16384 max positive raw value
		left_pressed=1;
		IMU_CharT=76;
	}
	else if(ax<-8192){
		right_pressed=1;
		IMU_CharT=82;
	}
	else if(ay>8192){
		down_pressed=1;
		IMU_CharT=68;
	}
	else if(ay<-8192){
		up_pressed=1;
		IMU_CharT=85;
	}else{
		IMU_CharT=78;
//		down_pressed=0;
//		left_pressed=0;
//		right_pressed=0;
//		up_pressed=0;
	}


	if(bat_move==1){
		bat_move=0;

		if(right_pressed==1)
		{
			right_pressed=0;
			//line below is for collision detection
			if(tball.batXpos>=5){
				tball.batXpos=tball.batXpos;
			}else if (tball.batXpos<5)
			{
				tball.batXpos=tball.batXpos+1;
			}
		}

		if(left_pressed==1)
		{
			left_pressed=0;
			//line below is for collision detection
			if(tball.batXpos<=0){
				tball.batXpos=tball.batXpos;
			}else if (tball.batXpos>0)
			{
				tball.batXpos=tball.batXpos-1;
			}
		}

		if(up_pressed==1)
		{
			up_pressed=0;
			//line below is for collision detection
			if(tball.batYpos1<=0){
				tball.batYpos1=tball.batYpos1;
				tball.batYpos2=tball.batYpos1+1;
			}else
				if (tball.batYpos1>0)
				{
					tball.batYpos1=tball.batYpos1-1;
					tball.batYpos2=tball.batYpos1+1;
				}

		}

		if(down_pressed==1)
		{
			down_pressed=0;
			//line below is for collision detection
			if(tball.batYpos1>=6){
				tball.batYpos1=tball.batYpos1;
				tball.batYpos2=tball.batYpos1+1;
			}else if (tball.batYpos1<6)
			{
				tball.batYpos1=tball.batYpos1+1;
				tball.batYpos2=tball.batYpos1+1;
			}
		}

		//ADC Movement not needed anymore
		//		int64_t sampled_value = 0;
		//		HAL_ADC_Start(&hadc1);
		//		HAL_ADC_PollForConversion(&hadc1, 10);
		//		sampled_value = HAL_ADC_GetValue(&hadc1);
		//		HAL_ADC_Stop(&hadc1);
		//		tball.batYpos1=((sampled_value*7)/4095);
		//		tball.batYpos2=tball.batYpos1+1;
		//		tball.batYpos1=((sampled_value*7)/4095);
		//		tball.batYpos2=tball.batYpos1+1;
	}

	if(tball.ballXpos<0)
	{
		tennis_gameStop();
	}


	display[tball.ballYpos][tball.ballXpos] = 1;
	display[tball.batYpos1][tball.batXpos] = 1;
	display[tball.batYpos2][tball.batXpos] = 1;

	if(uart_transmit_tball_pos==1)
	{
		uart_transmit_tball_pos = 0;
		tennis_message[2] = (tball.ballXpos + 48);
		tennis_message[3] = (tball.ballYpos + 48);
		tennis_message[4] = ((speed+1) + 48);
		tennis_message[5] = (ball_angle + 48);
		tennis_message[6] = (tball.batXpos + 48);
		tennis_message[7] = (tball.batYpos1 + 48);
		tennis_message[8] = (IMU_CharT);
		HAL_UART_Transmit(&huart2, (uint8_t*)tennis_message, 10, 50);
	}

}

void collision_detection()
{
	//weird top left cases
	if((tball.ballXpos-1==0) && (tball.ballYpos-1==-1) && (ball_angle==3))
	{
		if(tball.batYpos1==0)
		{
			ball_angle=2;
			Number_Of_Bounces++;
		}else
		{
			ball_angle=5;
		}
	}

	//weird bottom left cases
	if((tball.ballXpos-1==0) && (tball.ballYpos+1==8) && (ball_angle==5))
	{
		if(tball.batYpos1==6)
		{
			ball_angle=4;
			Number_Of_Bounces++;
		}else
		{
			ball_angle=3;
		}
	}

	//weird top cases edge of bat at top of matrix
	if((tball.ballXpos-1==tball.batXpos) && (tball.ballYpos-1==-1) && (ball_angle==3))
	{
		if(tball.batYpos1==0)
		{
			ball_angle=2;
			Number_Of_Bounces++;
		}else
		{
			ball_angle=5;
		}
	}

	//weird bottom cases edge of bat at bottom of matrix
	if((tball.ballXpos-1==tball.batXpos) && (tball.ballYpos+1==8) && (ball_angle==5))
	{
		if(tball.batYpos1==6)
		{
			ball_angle=4;
			Number_Of_Bounces++;
		}else
		{
			ball_angle=3;
		}
	}

	if(ball_angle==5) //hits bottom of bat while moving left down
	{
		if ((tball.ballXpos==tball.batXpos+1) && (tball.ballYpos==tball.batYpos2))
		{
			ball_angle=2;
			Number_Of_Bounces++;
		}
	}

	if(ball_angle==3) //hits top of bat while moving left up
	{
		if ((tball.ballXpos==tball.batXpos+1) && (tball.ballYpos==tball.batYpos1))
		{
			ball_angle=4;
			Number_Of_Bounces++;
		}
	}


	//start bounce down right
	if(ball_angle==0)
	{
		if ((tball.ballXpos==tball.batXpos+1) && (tball.ballYpos==tball.batYpos2))
		{
			ball_angle=2;
			Number_Of_Bounces++;
		}
	}

	//start bounce up right
	if(ball_angle==0)
	{
		if ((tball.ballXpos==tball.batXpos+1) && (tball.ballYpos==tball.batYpos1))
		{
			ball_angle=4;
			Number_Of_Bounces++;
		}
	}

	//edge bat case down right
	if(ball_angle==3){
		if ((tball.ballXpos==tball.batXpos+1) && (tball.ballYpos==tball.batYpos2+1))
		{
			ball_angle=2;
			Number_Of_Bounces++;
		}
	}

	//edge bat case up right
	if(ball_angle==5){
		if ((tball.ballXpos==tball.batXpos+1) && (tball.ballYpos==tball.batYpos1-1))
		{
			ball_angle=4;
			Number_Of_Bounces++;
		}
	}

	if(ball_angle==3)
	{
		//up right normal bounce off bat while ball moves up left into bat
		if ((tball.ballXpos==tball.batXpos+1) && (tball.ballYpos==tball.batYpos2))
		{
			ball_angle=4;
			Number_Of_Bounces++;
		}
	}

	if(ball_angle==5)
	{
		//down right normal bounce off bat while ball moves down left into bat
		if ((tball.ballXpos==tball.batXpos+1) && (tball.ballYpos==tball.batYpos1))
		{
			ball_angle=2;
			Number_Of_Bounces++;
		}
	}

	if(tball.ballXpos-1<0)//you lose, because ball missed bat
	{
		middle_pressed=1;
		tennis_gameStop();
	}

	if(tball.ballYpos-1<0) //hits top wall
	{
		//tball.ballYpos+=1;
		if(ball_angle==4) //up from left
		{
			ball_angle=2;
		}

		if(ball_angle==3) //up from right
		{
			ball_angle=5;
		}
	}

	if(tball.ballXpos+1>7) //hits right wall
	{
		//tball.ballXpos-=1;
		if(ball_angle==4) //up from left
		{
			ball_angle=3;
		}

		if(ball_angle==2) //down from right
		{
			ball_angle=5;
		}
	}

	if(tball.ballYpos+1>7) //hits bottom wall
	{
		//tball.ballYpos-=1;
		if(ball_angle==2) //down from left
		{
			ball_angle=4;
		}

		if(ball_angle==5) //down from right
		{
			ball_angle=3;
		}
	}


}



void move_ball()
{
	if(ball_angle==0)
	{
		tball.ballXpos=tball.ballXpos-1;
	}


	if(ball_angle==2)
	{
		tball.ballYpos=tball.ballYpos+1;
		tball.ballXpos=tball.ballXpos+1;

	}


	if(ball_angle==3)
	{
		tball.ballXpos=tball.ballXpos-1;
		tball.ballYpos=tball.ballYpos-1;

	}


	if(ball_angle==4)
	{
		tball.ballXpos=tball.ballXpos+1;
		tball.ballYpos=tball.ballYpos-1;

	}

	if(ball_angle==5)
	{

		tball.ballXpos=tball.ballXpos-1;
		tball.ballYpos=tball.ballYpos+1;
	}
}



void tennis_gameStop(){
	tennis_game_counter=0;
	TennisSysTickCounter=0;
	ball_angle=0;
}
