/******************** (C) COPYRIGHT 2009 Embest Info&Tech Co.,LTD. ************
* File Name          : led.c
* Author             : Wuhan R&D Center, Embest
* Date First Issued  : 07/12/2009
* Description        : This file provides firmware functions to manage
*                      7 sections of numerical code tubes.
*******************************************************************************
*******************************************************************************
* History:
* 07/12/2009		 : V1.0		   initial version
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "led.h"

const uint8_t DIGIT[] = { 0xFD, 0x61, 0xDB, 0xF3, 0x67, 0xB7, 0xBF, 0xE1, 0xFF, 0xF7 };	

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define GPIO_LED_PORT_x		GPIOE

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/** @defgroup Private Variables on Chip Select
  * @{
  */
GPIO_TypeDef* GPIO_SEL_PORT[CHIP_SEL_NUM] = {CHIP_SEL_1_GPIO_PORT,
                                             CHIP_SEL_2_GPIO_PORT,
											 CHIP_SEL_3_GPIO_PORT,
											 CHIP_SEL_4_GPIO_PORT};

const uint16_t GPIO_SEL_PIN[CHIP_SEL_NUM] = {CHIP_SEL_1_GPIO_PIN,
                                             CHIP_SEL_2_GPIO_PIN,
											 CHIP_SEL_3_GPIO_PIN,
											 CHIP_SEL_4_GPIO_PIN};



/** @defgroup STM32_EVAL_Private_Variables
  * @{
  */
GPIO_TypeDef* GPIO_LED_PORT[Four_LEDn] = {LED_A_GPIO_PORT, LED_B_GPIO_PORT,
									      LED_C_GPIO_PORT, LED_D_GPIO_PORT,
									      LED_E_GPIO_PORT, LED_F_GPIO_PORT,
								          LED_G_GPIO_PORT, LED_DP_GPIO_PORT};

const uint16_t GPIO_LED_PIN[Four_LEDn] = {LED_A_GPIO_PIN, LED_B_GPIO_PIN,
									      LED_C_GPIO_PIN, LED_D_GPIO_PIN,
									      LED_E_GPIO_PIN, LED_F_GPIO_PIN,
								          LED_G_GPIO_PIN, LED_DP_GPIO_PIN};
								  


/* Private function prototypes -----------------------------------------------*/ 
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Four LED Chip Select.
  * @param  Led: Specifies the Led to be configured. 
  *   This parameter can be one of following parameters:
  *     @arg LED_ONE
  *     @arg LED_TWO
  *     @arg LED_THREE
  *     @arg LED_FOUR
  *     @arg LED_ALL
  * @retval None
  */
void LED_CHIP_SEL(uint8_t led)
{
  switch (led)
  {
    case LED_ONE:
	  GPIO_SEL_PORT[0]->BRR  = GPIO_SEL_PIN[0];
	  GPIO_SEL_PORT[1]->BSRR = GPIO_SEL_PIN[1];
	  GPIO_SEL_PORT[2]->BSRR = GPIO_SEL_PIN[2];
	  GPIO_SEL_PORT[3]->BSRR = GPIO_SEL_PIN[3];
	  break;

    case LED_TWO:
	  GPIO_SEL_PORT[0]->BSRR = GPIO_SEL_PIN[0];
	  GPIO_SEL_PORT[1]->BRR  = GPIO_SEL_PIN[1];
	  GPIO_SEL_PORT[2]->BSRR = GPIO_SEL_PIN[2];
	  GPIO_SEL_PORT[3]->BSRR = GPIO_SEL_PIN[3];
	  break;

    case LED_THREE:
	  GPIO_SEL_PORT[0]->BSRR = GPIO_SEL_PIN[0];
	  GPIO_SEL_PORT[1]->BSRR = GPIO_SEL_PIN[1];
	  GPIO_SEL_PORT[2]->BRR  = GPIO_SEL_PIN[2];
	  GPIO_SEL_PORT[3]->BSRR = GPIO_SEL_PIN[3];
	  break;

    case LED_FOUR:
	  GPIO_SEL_PORT[0]->BSRR = GPIO_SEL_PIN[0];
	  GPIO_SEL_PORT[1]->BSRR = GPIO_SEL_PIN[1];
	  GPIO_SEL_PORT[2]->BSRR = GPIO_SEL_PIN[2];
	  GPIO_SEL_PORT[3]->BRR  = GPIO_SEL_PIN[3];
	  break;

    case LED_ALL:
	  GPIO_SEL_PORT[0]->BRR  = GPIO_SEL_PIN[0];
	  GPIO_SEL_PORT[1]->BRR  = GPIO_SEL_PIN[1];
	  GPIO_SEL_PORT[2]->BRR  = GPIO_SEL_PIN[2];
	  GPIO_SEL_PORT[3]->BRR  = GPIO_SEL_PIN[3];
	  break;  

    default:
      break; 
  }	

  /* LED is off by default after chip select */
  SEVEN_LED_Off(); 
}

/**
  * @brief  Make the selected LED display specified digital.
  * @param  data: Specifies the digital. 
  *   This parameter can be one of following parameters:
  *     @arg ZERO
  *     @arg ONE
  *     @arg TWO
  *     @arg THREE 
  *     @arg FOUR
  *     @arg FIVE
  *     @arg SIX
  *     @arg SEVEN
  *     @arg EIGHT
  *     @arg NINE             
  * @retval None
  */
void SEVEN_LED_DISPLAY(uint8_t data)
{
  switch (data)
  {
    case 0:
	  GPIO_LED_PORT_x->BRR  = GPIO_LED_PIN[0] | GPIO_LED_PIN[1] \
	                        | GPIO_LED_PIN[2] | GPIO_LED_PIN[3]	\
							| GPIO_LED_PIN[4] | GPIO_LED_PIN[5] \
							| GPIO_LED_PIN[7];
	  GPIO_LED_PORT_x->BSRR = GPIO_LED_PIN[6];
	  break;

    case 1:
	  GPIO_LED_PORT_x->BRR  = GPIO_LED_PIN[1] | GPIO_LED_PIN[2] \
							| GPIO_LED_PIN[7];
	  GPIO_LED_PORT_x->BSRR = GPIO_LED_PIN[0] | GPIO_LED_PIN[3]	\
	  						| GPIO_LED_PIN[4] | GPIO_LED_PIN[5] \
							| GPIO_LED_PIN[6];
	  break;

    case 2:
	  GPIO_LED_PORT_x->BRR  = GPIO_LED_PIN[0] | GPIO_LED_PIN[1] \
	                        | GPIO_LED_PIN[3] | GPIO_LED_PIN[4]	\
							| GPIO_LED_PIN[6] | GPIO_LED_PIN[7];
	  GPIO_LED_PORT_x->BSRR = GPIO_LED_PIN[2] | GPIO_LED_PIN[5];
	  break;

    case 3:
	  GPIO_LED_PORT_x->BRR  = GPIO_LED_PIN[0] | GPIO_LED_PIN[1] \
	                        | GPIO_LED_PIN[2] | GPIO_LED_PIN[3]	\
							| GPIO_LED_PIN[6] | GPIO_LED_PIN[7];
	  GPIO_LED_PORT_x->BSRR = GPIO_LED_PIN[4] | GPIO_LED_PIN[5];
	  break;

    case 4:
	  GPIO_LED_PORT_x->BRR  = GPIO_LED_PIN[1] | GPIO_LED_PIN[2] \
	                        | GPIO_LED_PIN[5] | GPIO_LED_PIN[6]	\
							| GPIO_LED_PIN[7];
	  GPIO_LED_PORT_x->BSRR = GPIO_LED_PIN[0] | GPIO_LED_PIN[3] \
	                        | GPIO_LED_PIN[4];
	  break;

    case 5:
	  GPIO_LED_PORT_x->BRR  = GPIO_LED_PIN[0] | GPIO_LED_PIN[2] \
	                        | GPIO_LED_PIN[3] | GPIO_LED_PIN[5]	\
							| GPIO_LED_PIN[6] | GPIO_LED_PIN[7];
	  GPIO_LED_PORT_x->BSRR = GPIO_LED_PIN[1] | GPIO_LED_PIN[4];
	  break;

    case 6:
	  GPIO_LED_PORT_x->BRR  = GPIO_LED_PIN[0] | GPIO_LED_PIN[2] \
	                        | GPIO_LED_PIN[3] | GPIO_LED_PIN[4]	\
							| GPIO_LED_PIN[5] | GPIO_LED_PIN[6] \
							| GPIO_LED_PIN[7];
	  GPIO_LED_PORT_x->BSRR = GPIO_LED_PIN[1];
	  break;

    case 7:
	  GPIO_LED_PORT_x->BRR  = GPIO_LED_PIN[0] | GPIO_LED_PIN[1] \
	                        | GPIO_LED_PIN[2] | GPIO_LED_PIN[7];
	  GPIO_LED_PORT_x->BSRR = GPIO_LED_PIN[3] | GPIO_LED_PIN[4] \
	                        | GPIO_LED_PIN[5] | GPIO_LED_PIN[6];
	  break;

    case 8:
	  GPIO_LED_PORT_x->BRR  = GPIO_LED_PIN[0] | GPIO_LED_PIN[1] \
	                        | GPIO_LED_PIN[2] | GPIO_LED_PIN[3]	\
							| GPIO_LED_PIN[4] | GPIO_LED_PIN[5] \
							| GPIO_LED_PIN[6] | GPIO_LED_PIN[7];
	  break;

    case 9:
	  GPIO_LED_PORT_x->BRR  = GPIO_LED_PIN[0] | GPIO_LED_PIN[1] \
	                        | GPIO_LED_PIN[2] | GPIO_LED_PIN[3]	\
							| GPIO_LED_PIN[5] | GPIO_LED_PIN[6] \
							| GPIO_LED_PIN[7];
	  GPIO_LED_PORT_x->BSRR = GPIO_LED_PIN[4];
	  break;

    default:
      break; 
  }
}

/**
  * @brief  Turn the selected LED off.
  * @param  None
  * @retval None
  */
void SEVEN_LED_Off(void)
{
  GPIO_LED_PORT_x->BSRR  = GPIO_LED_PIN[0] | GPIO_LED_PIN[1] \
	                     | GPIO_LED_PIN[2] | GPIO_LED_PIN[3]	\
					     | GPIO_LED_PIN[4] | GPIO_LED_PIN[5] \
					     | GPIO_LED_PIN[6] | GPIO_LED_PIN[7];
}


/************* (C) COPYRIGHT 2009 Wuhan R&D Center, Embest *****END OF FILE****/
