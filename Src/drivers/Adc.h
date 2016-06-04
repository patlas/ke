#ifndef __ADC_DRIVER_H
#define __ADC_DRIVER_H

#include "stm32f1xx_hal.h"
#include <stdint.h>

extern ADC_HandleTypeDef g_AdcHandle;

void Adc_init(void);

#endif
