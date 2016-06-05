#include "Adc.h"

static ADC_HandleTypeDef AdcHandle;
static volatile uint16_t ADCValue;
static TaskHandle_t  *tADC_handle = NULL;


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* AdcHandle)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	ADCValue = HAL_ADC_GetValue(AdcHandle);
	
	if(tADC_handle != NULL){
		xTaskNotifyFromISR(*tADC_handle,0,eNoAction,&xHigherPriorityTaskWoken);
	}
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void ADC1_2_IRQHandler()
{
		HAL_ADC_IRQHandler(&AdcHandle);
}

void Adc_registerTask(TaskHandle_t *handle){
	tADC_handle = handle;
}

uint16_t Adc_getValue(void){
	return ADCValue;
}

void ADC_start(void){
	HAL_ADC_Start_IT(&AdcHandle);
}

void Adc_init(void){
	
	GPIO_InitTypeDef gpioInit;
 
	__GPIOC_CLK_ENABLE();
  __ADC1_CLK_ENABLE();
 
	gpioInit.Pin = GPIO_PIN_4;
  gpioInit.Mode = GPIO_MODE_ANALOG;
  gpioInit.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &gpioInit);
 
  HAL_NVIC_SetPriority(ADC1_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(ADC1_IRQn);
 
  ADC_ChannelConfTypeDef adcChannel;
 
  AdcHandle.Instance = ADC1;
 
	AdcHandle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  AdcHandle.Init.ScanConvMode = DISABLE;
  AdcHandle.Init.ContinuousConvMode = ENABLE;
  AdcHandle.Init.DiscontinuousConvMode = DISABLE;
  AdcHandle.Init.NbrOfDiscConversion = 0;
  AdcHandle.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  AdcHandle.Init.NbrOfConversion = 1;
  
  adcChannel.Channel = ADC_CHANNEL_14;
  adcChannel.Rank = ADC_REGULAR_RANK_1;
  adcChannel.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
	
	HAL_ADC_Init(&AdcHandle);
	HAL_ADC_ConfigChannel(&AdcHandle, &adcChannel);
}
