#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

#define I2C_DELAY		4
void I2C_Delay(unsigned int time);
void I2C_Init();
void I2C_Start();
void I2C_Stop();
unsigned char I2C_CheckAck(void);
void I2C_Write(unsigned char Data);
unsigned char I2C_Read(void);
