#include "rtos_tasks.h"
#include "Adc.h"


/* data structs and semaphores */

void tCouter_task(void * pvParameters);
	
/* globals and queues */
QueueHandle_t joyPressQueue;

/* RTOS data initializer and creator */
static TaskHandle_t  tBlink_handle;
static TaskHandle_t	 tLCD_handle;
static TaskHandle_t  tMain_handle;
static TaskHandle_t	 tADC_handle;
static TaskHandle_t  tSOUND_handle;
static TaskHandle_t	 tLED_handler;
static TaskHandle_t	 tCounter_handler;
void RtosDataAndTaskInit(void)
{
	joyPressQueue = xQueueCreate(10 , 1);
	
	/* insert into queue value adequate to show menu at startup */
	uint8_t enter_menu = 16;
	xQueueSend( joyPressQueue, &enter_menu, NULL );
	
	xTaskCreate( tBlink_led, "BlinkTest", configMINIMAL_STACK_SIZE, NULL, 1, &tBlink_handle );
	//xTaskCreate( tLCD, "LCD", configMINIMAL_STACK_SIZE, NULL, 1, tLCD_handle );
	xTaskCreate( tMain_menu, "MainMenuTask", configMINIMAL_STACK_SIZE, NULL, 1, &tMain_handle );
	xTaskCreate( tADC_graph, "ADCgraphTask", configMINIMAL_STACK_SIZE, NULL, 1, &tADC_handle );
	vTaskSuspend(tADC_handle);
	xTaskCreate( tSound_generator, "SoundTask", configMINIMAL_STACK_SIZE, NULL, 1, &tSOUND_handle );
	xTaskCreate( tLED_counter, "LedTask", configMINIMAL_STACK_SIZE, NULL, 1, &tLED_handler );
	xTaskCreate( tCouter_task, "CounterTask", configMINIMAL_STACK_SIZE, NULL, 1, &tCounter_handler );

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

#define MENU_SIZE 4
#define SELECT_SIGN '+'
#define MENU_OFFSET 1

static inline void black_screen(bool *on)
{
	GLCD_Clear(Black);
}

static inline void white_screen(bool *on)
{
	GLCD_Clear(White);
}

static void sound_notify(uint8_t line, uint8_t str_size, bool *on)
{
	/*1const*/ uint8_t on_off[][3] = {"OFF", "ON "};
	GLCD_DisplayString(line, 2+str_size, on_off[(int)*on]); //TODO - check if works properly
}

static uint8_t sound_str[] = "GENERATE SOUND";
static bool sound_notification = false;
static void show_menu(bool *on)
{

	GLCD_Clear(White);
	GLCD_SetTextColor(Magenta);
	GLCD_DisplayString(MENU_OFFSET + 0,  1, "MENU:");
	GLCD_SetTextColor(DarkCyan);
	GLCD_DisplayString(MENU_OFFSET + 1,  2, "BLACK SCREEN");
	GLCD_DisplayString(MENU_OFFSET + 2,  2, "WHITE SCREEN");
	GLCD_DisplayString(MENU_OFFSET + 3,  2, sound_str);
	sound_notify(MENU_OFFSET + 3, sizeof(sound_str), &sound_notification); //TODO - check if works properly
	GLCD_DisplayString(MENU_OFFSET + 4,  2, "ADC GRAPH");
	//*on = !(*on);

}

static inline void show_adc_graph(bool *on)
{
	//start adc task
	if(on)
	{
		GLCD_Clear(Red);
		GLCD_SetTextColor(Black);
		GLCD_DisplayString(4,  0, "START ADC GRAPH TASK");
		vTaskResume(tADC_handle);
	}
	else
	{
		vTaskSuspend(tADC_handle);
	}
}

static inline void generate_sound(bool *on)
{
	*on = !(*on); //do not enter menu, only change viewed notify
	sound_notification = !sound_notification;
	sound_notify(MENU_OFFSET + 3, sizeof(sound_str), &sound_notification);
}

static void (*f_ptr[])(bool*) = {
	show_menu,
	black_screen,
	white_screen,
	generate_sound,
	show_adc_graph
	//in case of sound generating start task that generate sound and do not block menu task (the same priority)
};


void tMain_menu(void * pvParameters)
{
/* Joystick input                                                         */
  uint8_t joy = 16;
	int8_t position = 0;
	bool entered = true;
	
	for(;;)
	{
		
    xQueueReceive( joyPressQueue, &joy, portMAX_DELAY );
		switch(joy)
		{
			
			case 4:
				if(entered != true)
				{
					GLCD_DisplayChar(MENU_OFFSET+position, 1, ' ');
					position++;
				}
				break;
			
			case 8:
				if(entered != true)
				{	
					GLCD_DisplayChar(MENU_OFFSET+position, 1, ' ');
					position--;
				}
				break;
			
			case 16:
				entered = !entered;
				if(entered == false)
					position = 0;

				(*f_ptr[position])(&entered);
					
			}
		
		
		if(position > MENU_SIZE)
			position = 1;
		if(position < 1)
			position = MENU_SIZE;
		
		if(joy && !entered)
		{
			GLCD_SetTextColor(DarkGreen);
			GLCD_DisplayChar(MENU_OFFSET+position, 1, SELECT_SIGN);
			joy = 0;
		}
		
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

uint8_t dig1=0, dig2=0, dig3=0, dig4=0;
void tLED_counter(void * pvParameters)
{	
	printf("START LED counter");
	uint8_t disp_nr = 0;
	for(;;)
	{
		
		LED_CHIP_SEL(disp_nr);
	  SEVEN_LED_DISPLAY(dig4);
		vTaskDelay(2);
		LED_CHIP_SEL(disp_nr+1);
	  SEVEN_LED_DISPLAY(dig3);
		vTaskDelay(2);
		LED_CHIP_SEL(disp_nr+2);
	  SEVEN_LED_DISPLAY(dig2);
		vTaskDelay(2);
		LED_CHIP_SEL(disp_nr+3);
	  SEVEN_LED_DISPLAY(dig1);
		vTaskDelay(2);
	}
}

void tCouter_task(void * pvParameters)
{	
	printf("START Counter");

	for(;;)
	{
		if(++dig1 > 9)
		{
			dig1 = 0;
			if(++dig2 > 9)
			{
				dig2 = 0;
				if(++dig3 > 9)
				{
					dig3 = 0;
					if(++dig4 > 9)
						dig4 = 0;
				}
			}
		}
				
		vTaskDelay(300);
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
	uint32_t g_ADCValue;
	GLCD_Clear(Green);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(4,  0, "ADC GRAPH TASK");
	for(;;)
	{
//		HAL_ADC_Start(&g_AdcHandle);
//    for (;;)
//    {
//        if (HAL_ADC_PollForConversion(&g_AdcHandle, 1) == HAL_OK)
//        {
//            g_ADCValue = HAL_ADC_GetValue(&g_AdcHandle);
//            //g_MeasurementNumber++;
//        }
//				vTaskDelay(200);
//    }
		
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
