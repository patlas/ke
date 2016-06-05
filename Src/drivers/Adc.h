#ifndef __ADC_DRIVER_H
#define __ADC_DRIVER_H

#include "stm32f1xx_hal.h"
#include "rtos_tasks.h"
#include <stdint.h>

void ADC_start(void);
void Adc_registerTask(TaskHandle_t *handle);
uint16_t Adc_getValue(void);
void Adc_init(void);

#endif
