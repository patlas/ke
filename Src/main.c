#include "stm32f1xx_hal.h"

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

/* Custome indudes */
#include "rtos_tasks.h"
#include "hw_config.h"
#include "GLCD.h"

extern uint8_t  ESD_IMG[];
extern uint8_t ESD_IMG_WIDTH;
extern uint8_t ESD_IMG_HEIGHT;
int main(void)
{

	/* hardware init -> see inside function */
	hw_init();
	
	/****************** LCD TEST **********************************/
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(3,  9, "TEST");
	//GLCD_Bmp (0, 0, ESD_IMG_WIDTH, ESD_IMG_HEIGHT, ESD_IMG);
	/**************************************************************/
	
	
	/* set priority grouping - required by FreeRTOS */
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	/* init created tasks */
	RtosDataAndTaskInit();
	/* start scheduler */
	vTaskStartScheduler();
	/* infinite loop - should have never been reached */
	for(;;);
}



