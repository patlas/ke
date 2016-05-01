#include "rtos_tasks.h"


/* data structs and semaphores */


	
/* globals and queues */


/* RTOS data initializer and creator */
static TaskHandle_t  tBlink_handle;
static TaskHandle_t	 tLCD_handle;
static TaskHandle_t  tMain_handle;
static TaskHandle_t	 tADC_handle;
static TaskHandle_t  tSOUND_handle;
void RtosDataAndTaskInit(void)
{

	xTaskCreate( tBlink_led, "BlinkTest", configMINIMAL_STACK_SIZE, NULL, 1, tBlink_handle );
	//xTaskCreate( tLCD, "LCD", configMINIMAL_STACK_SIZE, NULL, 1, tLCD_handle );
	xTaskCreate( tMain_menu, "MainMenuTask", configMINIMAL_STACK_SIZE, NULL, 1, tMain_handle );
	xTaskCreate( tADC_graph, "ADCgraphTask", configMINIMAL_STACK_SIZE, NULL, 1, tADC_handle );
	xTaskCreate( tSound_generator, "SoundTask", configMINIMAL_STACK_SIZE, NULL, 1, tSOUND_handle );

}


void vApplicationStackOverflowHook(TaskHandle_t xTask, signed char *pcTaskName )
{
	//task stack overflow occured
	printf("STACK OVERFLOW!!!");
	for(;;);
}

void vApplicationMallocFailedHook( void )
{
	// memory allocation error occured - error in pvPortMalloc()
	printf("MALLOC ERROR!!! - pvPortMalloc()");
	for(;;);
}

#define MENU_SIZE 2
#define SELECT_SIGN '+'

static inline void black_screen(void)
{
	GLCD_Clear(Black);
}

static inline void white_screen(void)
{
	GLCD_Clear(White);
}

static void show_menu(uint8_t argv)
{
	/*const*/ uint8_t sound_str[] = "GENERATE SOUND";
	/*1const*/ uint8_t on_off[][3] = {"ON", "OFF"};
	
	GLCD_Clear(White);
	GLCD_SetTextColor(Blue);
	GLCD_DisplayString(0,  1, "Menu:");
	GLCD_DisplayString(1,  2, "BLACK SCREEN");
	GLCD_DisplayString(2,  2, "WHITE SCREEN");
	GLCD_DisplayString(3,  2, sound_str);
	GLCD_DisplayString(3,  2+sizeof(sound_str)+1, on_off[argv]); //TODO - check if works properly
	GLCD_DisplayString(4,  2, "ADC GRAPH");

}

static inline void _show_menu(void)
{
	show_menu(1);
}

static void (*f_ptr[])(void) = {
	black_screen,
	white_screen,
	_show_menu
	//in case of sound generating start task that generate sound and do not block menu task (the same priority)
};


void tMain_menu(void * pvParameters)
{
/* Joystick input                                                         */
  uint8_t joy = 0;
	int8_t position = 0;
	bool entered = false;
	
	for(;;)
	{
    if (!(GPIOD->IDR & (1 << 15))) joy = 1;  /* Joystick left            */
    if (!(GPIOD->IDR & (1 << 13))) joy = 2;  /* Joystick right           */
    if (!(GPIOD->IDR & (1 << 12))) joy = 4;  /* Joystick up              */
    if (!(GPIOD->IDR & (1 << 14))) joy = 8;  /* Joystick down            */
    if (!(GPIOD->IDR & (1 << 11))) joy = 16;  /* Joystick select          */
    
		switch(joy)
		{
			
			case 4:
				if(entered != true)
				{
					GLCD_DisplayChar(position+1, 1, ' ');
					position++;
				}
				break;
			
			case 8:
				if(entered != true)
				{	
					GLCD_DisplayChar(position+1, 1, ' ');
					position--;
				}
				break;
			
			case 16:
				entered = !entered;
				if(entered)
				{
					//function pointer array
					(*f_ptr[position])();
				}
				else
				{
					show_menu(0);
				}
		}
		
		
		
		
		if(position > MENU_SIZE)
			position = 0;
		if(position < 0)
			position = MENU_SIZE;
		
		if(joy)
		{
			GLCD_DisplayChar(position, 1, SELECT_SIGN);
			joy = 0;
		}
		
		vTaskDelay(200);
	}
}

void tBlink_led(void * pvParameters)
{	
	printf("START BLINK");
	for(;;)
	{
		// nie dodano konfiguracji giop (nie bd migac) ale task bd dzialal
		HAL_GPIO_WritePin(GPIOE, 1<<2, GPIO_PIN_SET);
		vTaskDelay(1000);

		HAL_GPIO_WritePin(GPIOE, 1<<2, GPIO_PIN_RESET);

		vTaskDelay(1000);
	}
}

void tLCD(void * pvParameters)
{	
	uint32_t disp_mode = 0;
	
	for(;;)
	{
		/* wait until task will be notified by e.g. buttone press */
		xTaskNotifyWait( 0x00, 0xffffffff, &disp_mode, portMAX_DELAY );
	}
}


void tADC_graph(void * pvParameters)
{	
	uint32_t disp_mode = 0;
	
	for(;;)
	{
		/* wait until task will be notified by e.g. buttone press */
		xTaskNotifyWait( 0x00, 0xffffffff, &disp_mode, portMAX_DELAY );
	}
}

void tSound_generator(void * pvParameters)
{	
	//do STH
	uint32_t disp_mode = 0;	
	for(;;)
	{
		/* wait until task will be notified by e.g. buttone press */
		xTaskNotifyWait( 0x00, 0xffffffff, &disp_mode, portMAX_DELAY );
	}
}
