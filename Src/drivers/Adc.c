#include "Adc.h"

ADC_HandleTypeDef g_AdcHandle;

void Adc_init(void){
	
	GPIO_InitTypeDef gpioInit;
 
	__GPIOC_CLK_ENABLE();
  __ADC1_CLK_ENABLE();
 
	gpioInit.Pin = GPIO_PIN_4;
  gpioInit.Mode = GPIO_MODE_ANALOG;
  gpioInit.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &gpioInit);
 
  HAL_NVIC_SetPriority(ADC1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(ADC1_IRQn);
 
  ADC_ChannelConfTypeDef adcChannel;
 
  g_AdcHandle.Instance = ADC1;
 
  g_AdcHandle.Init.ScanConvMode = DISABLE;
  g_AdcHandle.Init.ContinuousConvMode = ENABLE;
  g_AdcHandle.Init.DiscontinuousConvMode = DISABLE;
  g_AdcHandle.Init.NbrOfDiscConversion = 0;
  g_AdcHandle.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1;
  g_AdcHandle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  g_AdcHandle.Init.NbrOfConversion = 1;
 
  HAL_ADC_Init(&g_AdcHandle);
 
  adcChannel.Channel = ADC_CHANNEL_14;
  adcChannel.Rank = 1;
  adcChannel.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
	
	HAL_ADC_Init(&g_AdcHandle);
	HAL_ADC_ConfigChannel(&g_AdcHandle, &adcChannel);
}
