#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "stm32f1xx_it.h"

#include "FreeRTOS.h"
#include "queue.h"
extern QueueHandle_t joyPressQueue;

static uint16_t EXTI_TAB[] = {
	GPIO_PIN_11,
	GPIO_PIN_12,
	GPIO_PIN_13,
	GPIO_PIN_14,
	GPIO_PIN_15
};

static uint8_t JOY_MAP[] = {16, 2, 8, 1, 4}; // select, left, down, right, up

void EXTI15_10_IRQHandler(void)
{
	for(uint8_t i=0; i< (sizeof(EXTI_TAB)/sizeof(EXTI_TAB[0])); i++)
	{
		if(__HAL_GPIO_EXTI_GET_IT(EXTI_TAB[i]) != RESET) 
		{ 
			__HAL_GPIO_EXTI_CLEAR_IT(EXTI_TAB[i]);
			
			xQueueSendFromISR( joyPressQueue, &JOY_MAP[i], NULL );
			break;
		}
	}
	
}