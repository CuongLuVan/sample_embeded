#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_i2c.h"

#define I2Cx_RCC				RCC_APB1Periph_I2C1
#define I2Cx						I2C1
#define I2C_GPIO_RCC		RCC_APB2Periph_GPIOB
#define I2C_GPIO				GPIOB
#define I2C_PIN_SDA			GPIO_Pin_7
#define I2C_PIN_SCL			GPIO_Pin_6
#define DELAY_TIMEOUT   50000
#define BMP085_ADDRESS 0x77  // I2C address of BMP085






#define   SMPLRT_DIV      0x19   //0x07(125Hz)
#define   CONFIG         0x1A   //0x06(5Hz)
#define   GYRO_CONFIG      0x1B   //0x18(不自检，2000deg/s)
#define   ACCEL_CONFIG   0x1C   //0x01(不自检，2G，5Hz)
#define   ACCEL_XOUT_H   0x3B
#define   ACCEL_XOUT_L   0x3C
#define   ACCEL_YOUT_H   0x3D
#define   ACCEL_YOUT_L   0x3E
#define   ACCEL_ZOUT_H   0x3F
#define   ACCEL_ZOUT_L   0x40
#define   TEMP_OUT_H      0x41
#define   TEMP_OUT_L      0x42
#define   GYRO_XOUT_H      0x43
#define   GYRO_XOUT_L      0x44   
#define   GYRO_YOUT_H      0x45
#define   GYRO_YOUT_L      0x46
#define   GYRO_ZOUT_H      0x47
#define   GYRO_ZOUT_L      0x48
#define   PWR_MGMT_1      0x6B   //
#define   WHO_AM_I         0x75   //

// define forr old pressure
#define ADDR_PRESSURE 0x77 // Module address write mode
#define ADDR_R 0xEF // Module address read mode

#define CMD_RESET 0x1E // ADC reset command
#define CMD_ADC_READ 0x00 // ADC read command
#define CMD_ADC_CONV 0x40 // ADC conversion command
#define CMD_ADC_D1 0x00 // ADC D1 conversion
#define CMD_ADC_D2 0x10 // ADC D2 conversion
#define CMD_ADC_256 0x00 // ADC OSR=256
#define CMD_ADC_512 0x02 // ADC OSR=512
#define CMD_ADC_1024 0x04 // ADC OSR=1024
#define CMD_ADC_2048 0x06 // ADC OSR=2056
#define CMD_ADC_4096 0x08 // ADC OSR=4096
#define CMD_PROM_RD 0xA0 // Prom read command

#define SLAVE_ADDRESS		0x68 //DO 1101


void initI2CPressure(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_address_direction(uint8_t address, uint8_t direction);
void i2c_transmit(uint8_t byte);
uint8_t i2c_receive_ack(void);
uint8_t i2c_receive_nack(void);
void i2c_write(uint8_t address, uint8_t data);
void i2c_read(uint8_t address, uint8_t* data);
uint8_t Mpu_Read(unsigned char address_device,unsigned char address);
void Mpu_Write(unsigned char address_device,unsigned char address,unsigned char Data);

void cmd_reset(void);
unsigned long cmd_adc(char cmd);
unsigned int cmd_prom(char coef_num);
unsigned char crc4(unsigned int n_prom[]);
float getValueDataPressure(void);
float getValueTemperature(void);

void bmp085Calibration(void);
short bmp085GetTemperature(unsigned int ut);
long bmp085GetPressure(unsigned long up);
char bmp085Read(unsigned char address);
int bmp085ReadInt(unsigned char address);
unsigned int bmp085ReadUT(void);
unsigned long bmp085ReadUP(void);
float getDataPressureSensorBM085(void);
