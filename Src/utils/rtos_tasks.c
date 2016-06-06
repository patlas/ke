#include "rtos_tasks.h"
#include "Adc.h"
#include <inttypes.h>


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
	if(*on)
		GLCD_Clear(Black);
}

static inline void white_screen(bool *on)
{
	if(*on)
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
//if(!(*on))
//{
	GLCD_Clear(White);
	GLCD_SetTextColor(Magenta);
	GLCD_DisplayString(MENU_OFFSET + 0,  1, "MENU:");
	GLCD_SetTextColor(DarkCyan);
	GLCD_DisplayString(MENU_OFFSET + 1,  2, "BLACK SCREEN");
	GLCD_DisplayString(MENU_OFFSET + 2,  2, "WHITE SCREEN");
	GLCD_DisplayString(MENU_OFFSET + 3,  2, sound_str);
	//sound_notify(MENU_OFFSET + 3, sizeof(sound_str), &sound_notification); //TODO - check if works properly
	GLCD_DisplayString(MENU_OFFSET + 4,  2, "ADC GRAPH");
	//*on = !(*on);
//}
sound_notify(MENU_OFFSET + 3, sizeof(sound_str), &sound_notification); //TODO - check if works properly

}

static inline void show_adc_graph(bool *on)
{
	//start adc task
	if(*on)
	{
		GLCD_Clear(White);
		vTaskResume(tADC_handle);
	}
	else
	{
		vTaskSuspend(tADC_handle);
		//show_menu(NULL);
	}
}

static inline void generate_sound(bool *on)
{
	*on = !(*on); //do not enter menu, only change viewed notify
	sound_notification = !sound_notification;
	sound_notify(MENU_OFFSET + 3, sizeof(sound_str), &sound_notification);
	//*on = !(*on);
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
				//(*f_ptr[position])(&entered);
				if(entered == false)
				{
				  (*f_ptr[position])(&entered);
					position = 0;
				}
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

uint16_t adcData[320];
uint16_t samplesStored = 0;
uint32_t sum = 0;
uint32_t sumCnt = 0;

void tADC_graph(void * pvParameters)
{	
	uint32_t disp_mode = 0;
	uint32_t i;
	taskENTER_CRITICAL();
	GLCD_Clear(White);
	taskEXIT_CRITICAL();
	Adc_registerTask(&tADC_handle);
	ADC_start();
	for(;;)
	{
		xTaskNotifyWait( 0x00, 0xffffffff, &disp_mode, portMAX_DELAY );
		if(sumCnt < 16384){
			sum += Adc_getValue();
			sumCnt++;
		}else{
			sumCnt = 0;
			if(samplesStored < 320){
				samplesStored++;
			}else{
				for(i = 0; i < (samplesStored-1); i++){
					adcData[i] = adcData[i+1];
				}
			}
			adcData[samplesStored-1] = sum/16384;
			sum = 0;
			for(i = 0; i < samplesStored; i++){
				taskENTER_CRITICAL();
				GLCD_Bargraph(i,0,1,240,adcData[i]*1024/4038);
				taskEXIT_CRITICAL();
			}
		}
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
