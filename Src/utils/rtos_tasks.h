#include <stdint.h>
#include <stdio.h>
#include "stm32f1xx_hal.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "utils.h"

#define PRIORITY_BASIC 1
#define PRIORITY_MAX configMAX_PRIORITIES


void RtosDataAndTaskInit(void);

void tBlink_led(void * pvParameters); //uint8_t nr, uint16_t delay_ms)

