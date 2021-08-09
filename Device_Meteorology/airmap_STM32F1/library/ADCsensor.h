#include "stm32f10x.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_adc.h"


#define HUMIDITY_SENSOR 1
#define TEMP_SENSOR 0
#define  NUMBER_TO_VOLTIVE_ADC 1240


void setupAllADCSensor(void);
float sensorWindyResult(void);
uint32_t sensorGetHumidity_TemperatureResult(void);
