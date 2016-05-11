/******************** (C) COPYRIGHT 2009 Embest Info&Tech Co.,LTD. ************
* File Name          : led.h
* Author             : Wuhan R&D Center, Embest
* Date First Issued  : 07/12/2009
* Description        : This file contains definitions for STM3210C_EVAL's 
*                      7 sections of numerical code tubes.
*******************************************************************************
*******************************************************************************
* History:
* 07/12/2009		 : V1.0		   initial version
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_H
#define __LED_H

/* Includes ------------------------------------------------------------------*/

#include "stm32f1xx_hal.h"
#include <stdint.h>

typedef enum 
{
  LED_A  = 0,
  LED_B  = 1,
  LED_C  = 2,
  LED_D  = 3,
  LED_E  = 4,
  LED_F  = 5,
  LED_G  = 6,
  LED_DP = 7
} SEVEN_LED_TypeDef;

typedef enum 
{
  LED_ONE   = 0,
  LED_TWO   = 1,
  LED_THREE = 2,
  LED_FOUR  = 3,
  LED_ALL	= 4
} SEL_LED_TypeDef;

/** @addtogroup Chip Select
  * @{
  */
#define CHIP_SEL_NUM				4

#define CHIP_SEL_1_GPIO_PORT		GPIOC
#define CHIP_SEL_1_GPIO_CLK			RCC_APB2Periph_GPIOC		
#define CHIP_SEL_1_GPIO_PIN			GPIO_PIN_7

#define CHIP_SEL_2_GPIO_PORT		GPIOC
#define CHIP_SEL_2_GPIO_CLK			RCC_APB2Periph_GPIOC		
#define CHIP_SEL_2_GPIO_PIN			GPIO_PIN_5

#define CHIP_SEL_3_GPIO_PORT		GPIOC
#define CHIP_SEL_3_GPIO_CLK			RCC_APB2Periph_GPIOC		
#define CHIP_SEL_3_GPIO_PIN			GPIO_PIN_3

#define CHIP_SEL_4_GPIO_PORT		GPIOC
#define CHIP_SEL_4_GPIO_CLK			RCC_APB2Periph_GPIOC		
#define CHIP_SEL_4_GPIO_PIN			GPIO_PIN_2		


/** @addtogroup STM3210C_EVAL_LED
  * @{
  */  
#define Four_LEDn                    8

#define LED_A_GPIO_PORT              GPIOE
#define LED_A_GPIO_CLK               RCC_APB2Periph_GPIOE  
#define LED_A_GPIO_PIN               GPIO_PIN_8
  
#define LED_B_GPIO_PORT              GPIOE
#define LED_B_GPIO_CLK               RCC_APB2Periph_GPIOE  
#define LED_B_GPIO_PIN               GPIO_PIN_9
  
#define LED_C_GPIO_PORT              GPIOE
#define LED_C_GPIO_CLK               RCC_APB2Periph_GPIOE  
#define LED_C_GPIO_PIN               GPIO_PIN_10
  
#define LED_D_GPIO_PORT              GPIOE
#define LED_D_GPIO_CLK               RCC_APB2Periph_GPIOE  
#define LED_D_GPIO_PIN               GPIO_PIN_11

#define LED_E_GPIO_PORT              GPIOE
#define LED_E_GPIO_CLK               RCC_APB2Periph_GPIOE  
#define LED_E_GPIO_PIN               GPIO_PIN_12

#define LED_F_GPIO_PORT              GPIOE
#define LED_F_GPIO_CLK               RCC_APB2Periph_GPIOE  
#define LED_F_GPIO_PIN               GPIO_PIN_13

#define LED_G_GPIO_PORT              GPIOE
#define LED_G_GPIO_CLK               RCC_APB2Periph_GPIOE  
#define LED_G_GPIO_PIN               GPIO_PIN_14	

#define LED_DP_GPIO_PORT             GPIOE
#define LED_DP_GPIO_CLK              RCC_APB2Periph_GPIOE  
#define LED_DP_GPIO_PIN              GPIO_PIN_15

/** @addtogroup Values of digital singal 0 1 2 3 4 5 6 7 8 9 
  * @{
  */	



void LED_CHIP_SEL(uint8_t led);
void SEVEN_LED_DISPLAY(uint8_t data);
void SEVEN_LED_Off(void);
	
int Leds_main(void);

#endif

/************* (C) COPYRIGHT 2009 Wuhan R&D Center, Embest *****END OF FILE****/
