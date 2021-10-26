/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    stm32f1xx_it.c
 * @brief   Interrupt Service Routines.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */
int sysTickCounter=0;
extern volatile int64_t TennisSysTickCounter;

volatile int64_t FlickerCounter;

extern volatile int8_t middle_pressed;
extern volatile int8_t right_pressed;
extern volatile int8_t left_pressed;
extern volatile int8_t up_pressed;
extern volatile int8_t down_pressed;
extern volatile int8_t uart_transmit_ball_pos;
extern volatile int8_t end_flicker;
extern volatile int8_t end_toggle;
extern volatile int8_t player_toggle;
extern volatile int8_t ball_visible;
extern volatile int8_t goal_visible;
extern volatile int8_t ball_move;
extern volatile int8_t bat_move;
extern volatile int8_t uart_transmit_tball_pos;

extern volatile int8_t maze_ball_allowed_to_move;


int8_t middle_pressed_prev = 1;
int8_t right_pressed_prev;
int8_t left_pressed_prev;
int8_t up_pressed_prev;
int8_t down_pressed_prev;
int64_t ball_refresh_rate=700;
extern int16_t Number_Of_Bounces;
int64_t button_bounce_timer = 0;
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */
	display_matrix();
	sysTickCounter++;
	TennisSysTickCounter++;

	FlickerCounter++;

	if(sysTickCounter%300 == 0)
	{
		//player_toggle=1;
		ball_visible*=-1;
		maze_ball_allowed_to_move=1;
		//set UART Transmit OK flag for maze game
		uart_transmit_ball_pos=1;

	}

	//check if 100ms passed
	if(sysTickCounter%100==0)
	{
		//set end goal toggle
		end_flicker=1;
		end_toggle=1;
		goal_visible*=-1;
		bat_move=1;
		uart_transmit_tball_pos=1; //set flag to uart ball&bat position for tennis game
	}



	if (button_bounce_timer == 0 && HAL_GPIO_ReadPin(GPIOA, S3_Pin) != middle_pressed_prev)
	{
		//button de-bouncing
		if (HAL_GPIO_ReadPin(GPIOA, S3_Pin) == 0) {
			middle_pressed = 1;
			button_bounce_timer = 1;
		}
		middle_pressed_prev=HAL_GPIO_ReadPin(GPIOA, S3_Pin);
	}

	if (button_bounce_timer == 0 && HAL_GPIO_ReadPin(GPIOA, S4_Pin)!=right_pressed_prev)
	{
		//button de-bouncing
		if (HAL_GPIO_ReadPin(GPIOA, S4_Pin)==0) {
			right_pressed = 1;
			button_bounce_timer = 1;
		}

//		right_pressed=1;
		right_pressed_prev=HAL_GPIO_ReadPin(GPIOA, S4_Pin);
	}


	if (button_bounce_timer == 0 && HAL_GPIO_ReadPin(GPIOC, S2_Pin)!=left_pressed_prev)
	{
		//button de-bouncing
		if (HAL_GPIO_ReadPin(GPIOC, S2_Pin)==0) {
			left_pressed = 1;
			button_bounce_timer = 1;
		}

		left_pressed_prev=HAL_GPIO_ReadPin(GPIOC, S2_Pin);
	}

	if (button_bounce_timer == 0 && HAL_GPIO_ReadPin(GPIOB, S1_Pin)!=up_pressed_prev)
	{
		//button de-bouncing
		if (HAL_GPIO_ReadPin(GPIOB, S1_Pin)==0) {
			up_pressed = 1;
			button_bounce_timer = 1;
		}

		up_pressed_prev=HAL_GPIO_ReadPin(GPIOB, S1_Pin);
	}

	if (button_bounce_timer == 0 && HAL_GPIO_ReadPin(GPIOC, S5_Pin)!=down_pressed_prev)
	{
		//button de-bouncing
		if (HAL_GPIO_ReadPin(GPIOC, S5_Pin)==0) {
			down_pressed = 1;
			button_bounce_timer = 1;
		}

		down_pressed_prev=HAL_GPIO_ReadPin(GPIOC, S5_Pin);
	}

//	middle_pressed_prev=HAL_GPIO_ReadPin(GPIOA, S3_Pin);
	if (button_bounce_timer > 50) button_bounce_timer = 0; //Button bounce reset
	else if (button_bounce_timer != 0) button_bounce_timer++;

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */

  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */

  /* USER CODE END EXTI15_10_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
