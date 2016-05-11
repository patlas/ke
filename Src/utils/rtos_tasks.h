#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "stm32f1xx_hal.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

#include "GLCD.h"
#include "led.h"

#define PRIORITY_BASIC 1
#define PRIORITY_MAX configMAX_PRIORITIES


void RtosDataAndTaskInit(void);

void tBlink_led(void * pvParameters); //uint8_t nr, uint16_t delay_ms)
void tMain_menu(void * pvParameters);
void tADC_graph(void * pvParameters);
void tSound_generator(void * pvParameters);
void tLED_counter(void * pvParameters);
