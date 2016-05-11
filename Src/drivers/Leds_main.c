/******************** (C) COPYRIGHT 2009 Embest Info&Tech Co.,LTD. ************
* File Name          : main.c
* Author             : Wuhan R&D Center, Embest
* Date First Issued  : 07/12/2009
* Description        : Main program body
*******************************************************************************
*******************************************************************************
* History:
* 07/12/2009		 : V1.0		   initial version
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>                          /* standard I/O .h-file           */

#include "led.h" 


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//#define TEST_LED			LED_ALL

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void Leds_RCC_Configuration(void);
void Leds_GPIO_Configuration(void);
void LEDInit(void);
void Leds_Delay(unsigned int ticks);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int Leds_main(void)
{
  /* System Clocks Configuration */
  Leds_RCC_Configuration();

  /* Configure the GPIO ports */
  Leds_GPIO_Configuration();
  return 0;
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void Leds_RCC_Configuration(void)
{

  __HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

}

/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
void Leds_GPIO_Configuration(void)
{
  __HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure PC.02 PC.03 PC.05 PC.07 as Push-pull output ---------------------*/
  GPIO_InitStructure.Pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_7;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* Configure PE.08...15 as Push-pull output ----------------------------------*/
  GPIO_InitStructure.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 	 \
  								| GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13  \
								| GPIO_PIN_14 | GPIO_PIN_15;			   \
								
					
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStructure); 

  /* LED is off by default */
  SEVEN_LED_Off();
}


/**
  * @brief  Delay about ticks ms.
  * @param  ticks
  * @retval None
  */
void Leds_Delay(unsigned int ticks)
{
  int i, j;
  for (i = ticks; i > 0; i--)
  	for (j = 10000; j > 0; j--);
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/************* (C) COPYRIGHT 2009 Wuhan R&D Center, Embest *****END OF FILE****/
