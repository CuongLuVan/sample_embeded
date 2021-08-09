#include <ADCsensor.h>
#include <math.h>
#include "define.h"
#include "debug.h" 
#define ADC1_DR_Address    ((uint32_t)0x4001244C)
#define ADC2_DR_Address    ((uint32_t)0x4001284C)
#define ADC3_DR_Address    ((uint32_t)0x40013C4C)
static uint16_t ADCValue[3] = {10,28,20};
/*****************************************************************************
function:  setupAllADCSensor
argunent: float
return : uint8_t
description : function to setup All Sensor read data by ADC
Create date : 19/2/2017
user cread : Lu Van Cuong
****************************************************************************/
void setupAllADCSensor(void){
	ADC_InitTypeDef ADC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	printDebug("START: setupAllADCSensor"); 
  
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
   /* Enable ADC1 and GPIOC clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOA, ENABLE);
	 /* Configure PC.04 (ADC Channel14) as analog input -------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

	
	  /* DMA1 channel1 configuration ----------------------------------------------*/
  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCValue[0];
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 3;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  
  /* Enable DMA1 channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);
  
  /* ADC1 configuration ------------------------------------------------------*/
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 3;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channel14 configuration */ 
	//ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 3, ADC_SampleTime_55Cycles5);
	
  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* Enable ADC1 reset calibration register */   
  ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));

  /* Start ADC1 calibration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));
  /* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	printDebug("End: setupAllADCSensor"); 
}

/*****************************************************************************
function:  sensorWindyResult
argunent: float
return : uint8_t
description : function to get value CO2 sensor
Create date : 19/2/2017
user cread : Lu Van Cuong
****************************************************************************/
float sensorWindyResult(void)
{	
	return (ADCValue[2]*12*3.3)/4096;
}
/*****************************************************************************
function:  sensorGetHumidity_TemperatureResult
argunent: uint32_t
return : uint8_t
description : function to get value temperature and himidity sensor
Create date : 19/2/2017
user cread : Lu Van Cuong
reviewer:
****************************************************************************/
uint32_t sensorGetHumidity_TemperatureResult(void)
{ 
		  uint32_t result;
	    uint16_t temp,humi;
			float rawhumi;
			float rawtemp;
			float powercompaire;
			float power3_3V;
			power3_3V=3.3;
			powercompaire=4096/3.3;
			rawhumi = ADCValue[HUMIDITY_SENSOR]/powercompaire;
			rawtemp = ADCValue[TEMP_SENSOR]/powercompaire;
			rawhumi=(-12.5 +125*(rawhumi/power3_3V));
			rawtemp=(-66.875 + 218.75*(rawtemp/power3_3V));
			temp=(uint16_t)rawtemp;
			humi=(uint16_t)rawhumi;
			//printDebugF1(" sensorGetHumidity_TemperatureResult rawhumidata1=>%fV",rawhumidata1);
			//printDebugF1(" sensorGetHumidity_TemperatureResult rawhumidata2=>%fV",rawtempdata1);
			printDebug1(" raw temp VPIN=>%dV",temp);
		  printDebug1(" raw humi VPIN=>%dV",humi);
			result=humi<<16|temp;
			return result; 		
}

