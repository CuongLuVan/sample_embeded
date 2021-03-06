#include "i2csensor.h"
#include <stdio.h>
#include <math.h> 
#include "define.h"
#include "debug.h" 

const unsigned char OSS = 0;  // Oversampling Setting

// Calibration values
static int ac1;
static int ac2; 
static int ac3; 
static unsigned int ac4;
static unsigned int ac5;
static unsigned int ac6;
static int b1; 
static int b2;
static int mb;
static int mc;
static int md;

// b5 is calculated in bmp085GetTemperature(...), this variable is also used in bmp085GetPressure(...)
// so ...Temperature(...) must be called before ...Pressure(...).
static long b5; 

static short temperature;
static long pressure;

// Use these for altitude conversions
const float p0 = 101325;     // Pressure at sea level (Pa)
static float altitude;


/*---------------------------------------------------------------------*/
/*static unsigned int D1_4096;
static unsigned int D2_4096; 

static unsigned int D1_2048;
static unsigned int D2_2048; 

static unsigned int D1_1024;
static unsigned int D2_1024; 

static unsigned int D1_512;
static unsigned int D2_512; 

static unsigned int D1_256;
static unsigned int D2_256;*/ 
/*---------------------------------------------------------------------*/
static unsigned int D1; // ADC value of the pressure conversion
static unsigned int D2; // ADC value of the temperature conversion
static unsigned int C[8]; // calibration coefficients
static float P; // compensated pressure value
static float T; // compensated temperature value
static float dT; // difference between actual and measured temperature
static float OFF; // offset at actual temperature
static float SENS; // sensitivity at actual temperature
static int i;
static unsigned char n_crc; // crc value of the prom

void delay(int t){
	int k;
	while(t--){
		for(k=0;k<1000;k++);
	}

}

void initI2CPressure(void)
{
	// Initialization struct
	I2C_InitTypeDef I2C_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	printDebug("START:~~~~~~~A");
	// Step 1: Initialize I2C
	RCC_APB1PeriphClockCmd(I2Cx_RCC, ENABLE);
	I2C_InitStruct.I2C_ClockSpeed = 100000;
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStruct.I2C_OwnAddress1 = 0x00;
	I2C_InitStruct.I2C_Ack = I2C_Ack_Disable;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2Cx, &I2C_InitStruct);
	I2C_Cmd(I2Cx, ENABLE);
	printDebug("START:~~~~~~~B");
	// Step 2: Initialize GPIO as open drain alternate function
	RCC_APB2PeriphClockCmd(I2C_GPIO_RCC, ENABLE);
	GPIO_InitStruct.GPIO_Pin = I2C_PIN_SCL | I2C_PIN_SDA;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(I2C_GPIO, &GPIO_InitStruct);
	printDebug("START:~~~~~~~0");	
	bmp085Calibration();
	
	/*
	D1=0;
	D2=0;
	cmd_reset(); // reset IC
	for (i=0;i<8;i++){ C[i]=cmd_prom(i);} // read coefficients
	n_crc=crc4(C); // calculate the CRC
	if(!n_crc) printDebug("ERROR DATA");	*/
}

void i2c_start()
{
	int timeout=0;
	uint8_t buck=0;
	// Wait until I2Cx is not busy anymore
	timeout=DELAY_TIMEOUT;
	
	while (I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY)){
		timeout--;
		if(!timeout) { buck=1; break;}
	}
	if(buck) printDebug("ERROR i2c_start 2");
	// Generate start condition
	I2C_GenerateSTART(I2Cx, ENABLE);
	
	// Wait for I2C EV5. 
	// It means that the start condition has been correctly released 
	// on the I2C bus (the bus is free, no other devices is communicating))
	timeout=DELAY_TIMEOUT;
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT)){
		timeout--;
		if(!timeout) { buck=1; break;}
	}
		if(buck) printDebug("ERROR i2c_start 2");
	if(buck) printDebug("ERROR CONNECTIon I2C");
}

void i2c_stop(void)
{
	int timeout=0;
	uint8_t buck=0;
	// Generate I2C stop condition
	I2C_GenerateSTOP(I2Cx, ENABLE);
	// Wait until I2C stop condition is finished
	timeout=DELAY_TIMEOUT;
	while (I2C_GetFlagStatus(I2Cx, I2C_FLAG_STOPF)){
		timeout--;
		if(!timeout) { buck=1; break;}
	}
	if(buck) printDebug("ERROR CONNECTIon I2C");
}

void i2c_address_direction(uint8_t address, uint8_t direction)
{
	int timeout=0;
	uint8_t buck=0;	
	// Send slave address
	I2C_Send7bitAddress(I2Cx, address, direction);
	
	// Wait for I2C EV6
	// It means that a slave acknowledges his address
	timeout=DELAY_TIMEOUT;
	if (direction == I2C_Direction_Transmitter)
	{
		while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)){
			timeout--;
			if(!timeout) { buck=1; break;}
		}
	}
	else if (direction == I2C_Direction_Receiver)
	{	
		while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)){
			timeout--;
			if(!timeout) { buck=1; break;}
		}
	}
	if(buck) printDebug("ERROR i2c_start 3");
	if(buck) printDebug("ERROR CONNECTIon I2C");
}

void i2c_transmit(uint8_t byte)
{
	int timeout=0;
	uint8_t buck=0;	
	// Send data byte
	I2C_SendData(I2Cx, byte);
	// Wait for I2C EV8_2.
	// It means that the data has been physically shifted out and 
	// output on the bus)
	timeout=DELAY_TIMEOUT;
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED)){
			timeout--;
			if(!timeout) { buck=1; break;}
	}
	if(buck) printDebug("ERROR CONNECTIon I2C");
}

uint8_t i2c_receive_ack()
{
	int timeout=0;
	//uint8_t buck=0;	
	// Enable ACK of received data
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
	// Wait for I2C EV7
	// It means that the data has been received in I2C data register
	timeout=DELAY_TIMEOUT;
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED)){
			timeout--;
			if(!timeout) {  break;}
	}
	// Read and return data byte from I2C data register
	return I2C_ReceiveData(I2Cx);
}

uint8_t i2c_receive_nack()
{
	int timeout=0;
	//uint8_t buck=0;	
	// Disable ACK of received data
	I2C_AcknowledgeConfig(I2Cx, DISABLE);
	// Wait for I2C EV7
	// It means that the data has been received in I2C data register
	timeout=DELAY_TIMEOUT;
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED)){
			timeout--;
			if(!timeout) {  break;}
	}
	// Read and return data byte from I2C data register
	return I2C_ReceiveData(I2Cx);
}

void i2c_write(uint8_t address, uint8_t data)
{
	printDebug("START:~~~~~~~i2c_write");
	i2c_start();
	i2c_address_direction(address << 1, I2C_Direction_Transmitter);
	i2c_transmit(data);
	i2c_stop();
}

void i2c_read(uint8_t address, uint8_t* data)
{
	i2c_start();
	i2c_address_direction(address << 1, I2C_Direction_Receiver);
	*data = i2c_receive_nack();
	i2c_stop();
}


uint8_t Mpu_Read(unsigned char address_device,unsigned char address)
{
   uint8_t Data;
   i2c_write(address_device,address);
   i2c_read(address_device,&Data);
   return Data;
}
void Mpu_Write(unsigned char address_device,unsigned char address,unsigned char Data)
{
	i2c_start();
	i2c_address_direction(address_device << 1, I2C_Direction_Transmitter);
	i2c_transmit(address);
	i2c_transmit(Data);
	i2c_stop();
}

/*



*/

void cmd_reset(void)
{
	 i2c_write(ADDR_PRESSURE,CMD_RESET); // send reset sequence
	 delay(13); // wait for the reset sequence timing
}
//********************************************************
//! @brief preform adc conversion
//!
//! @return 24bit result
//********************************************************
unsigned long cmd_adc(char cmd)
{
	 unsigned int ret;
	 unsigned long temp=0;
	 i2c_write(ADDR_PRESSURE,CMD_ADC_CONV+cmd); // send conversion command
	 switch (cmd & 0x0f) // wait necessary conversion time
	 {
		 case CMD_ADC_256 : delay(1); break;
		 case CMD_ADC_512 : delay(3); break;
		 case CMD_ADC_1024: delay(4); break;
		 case CMD_ADC_2048: delay(6); break;
		 case CMD_ADC_4096: delay(10); break; 
	 }
	 i2c_write(ADDR_PRESSURE,CMD_ADC_READ);
	 
	 i2c_start();
	 i2c_address_direction(ADDR_PRESSURE<<1, I2C_Direction_Receiver);
	 ret=i2c_receive_ack();
	 temp=65536*ret;
	 ret=i2c_receive_ack();
	 temp=temp+256*ret;
	 ret= i2c_receive_nack();
	 temp=temp+ret;
	 i2c_stop(); // send stop condition
  return temp;
}
//********************************************************
//! @brief Read calibration coefficients
//!
//! @return coefficient
//********************************************************
unsigned int cmd_prom(char coef_num)
{
	 unsigned int ret;
	 unsigned int rC=0;

	 i2c_write(ADDR_PRESSURE,CMD_PROM_RD+coef_num*2); // send PROM READ command
	 i2c_start();
	 i2c_address_direction(ADDR_PRESSURE<<1, I2C_Direction_Receiver);
	 ret=i2c_receive_ack();
	 rC=rC+256*ret;
	 ret= i2c_receive_nack();
	 rC=rC+ret;
	 i2c_stop(); // send stop condition
	
 return rC;
}
//********************************************************
//! @brief calculate the CRC code
//!
//! @return crc code
//********************************************************
unsigned char crc4(unsigned int n_prom[])
{
	 int cnt; // simple counter
	 unsigned int n_rem; // crc reminder
	 unsigned int crc_read; // original value of the crc
	 unsigned char n_bit;
	 n_rem = 0x00;
	 crc_read=n_prom[7]; //save read CRC
	 n_prom[7]=(0xFF00 & (n_prom[7])); //CRC byte is replaced by 0
	 for (cnt = 0; cnt < 16; cnt++) // operation is performed on bytes
	 {// choose LSB or MSB
		 if (cnt%2==1) n_rem ^= (unsigned short) ((n_prom[cnt>>1]) & 0x00FF);
		 else n_rem ^= (unsigned short) (n_prom[cnt>>1]>>8);
		 for (n_bit = 8; n_bit > 0; n_bit--)
		 {
			 if (n_rem & (0x8000))
			 {
				n_rem = (n_rem << 1) ^ 0x3000;
			 }
			 else
			 {
				n_rem = (n_rem << 1);
			 }
		 }
	 }
	 n_rem= (0x000F & (n_rem >> 12)); // final 4-bit reminder is CRC code 
	 n_prom[7]=crc_read; // restore the crc_read to its original place
	 
	 return (n_rem ^ 0x0);
}
//********************************************************
//! @brief main program
//!
//! @return 0
//********************************************************
float getValueDataPressure(void)
{
	/*---------------------------------------------------------------------*/
		/*D2_4096=cmd_adc(CMD_ADC_D2+CMD_ADC_4096); // read D2
		D1_4096=cmd_adc(CMD_ADC_D1+CMD_ADC_4096); // read D1
	
		D2_2048=cmd_adc(CMD_ADC_D2+CMD_ADC_2048); // read D2
		D1_2048=cmd_adc(CMD_ADC_D1+CMD_ADC_2048); // read D1
	
	  D2_1024=cmd_adc(CMD_ADC_D2+CMD_ADC_1024); // read D2
		D1_1024=cmd_adc(CMD_ADC_D1+CMD_ADC_1024); // read D1
	
	  D2_512=cmd_adc(CMD_ADC_D2+CMD_ADC_512); // read D2
		D1_512=cmd_adc(CMD_ADC_D1+CMD_ADC_512); // read D1
	
		D2_256=cmd_adc(CMD_ADC_D2+CMD_ADC_256); // read D2
		D1_256=cmd_adc(CMD_ADC_D1+CMD_ADC_256); // read D1*/	
		/*---------------------------------------------------------------------*/
	
		// calcualte 1st order pressure and temperature (MS5607 1st order algorithm)
	
		D2=cmd_adc(CMD_ADC_D2+CMD_ADC_1024); // read D2
		D1=cmd_adc(CMD_ADC_D1+CMD_ADC_1024); // read D1
		dT=D2-C[5]*pow(2,8);
		OFF=C[2]*pow(2,17)+dT*C[4]/pow(2,6);
		SENS=C[1]*pow(2,16)+dT*C[3]/pow(2,7);
		
		T=(2000+(dT*C[6])/pow(2,23))/100;
		P=(((D1*SENS)/pow(2,21)-OFF)/pow(2,15))/100;
		//T=2000+(dT*C[6])/pow(2,23);
		//P=((D1*SENS)/pow(2,21)-OFF)/pow(2,15);
    printDebugF1("End:uint8_t getValueDataPressure=>%f",P); 
		printDebug1("End:uint8_t getValue C1 =>%d",C[1]);
		printDebug1("End:uint8_t getValue C2 =>%d",C[2]);
		printDebug1("End:uint8_t getValue C3 =>%d",C[3]);
		printDebug1("End:uint8_t getValue C4 =>%d",C[4]);
		printDebug1("End:uint8_t getValue C5 =>%d",C[5]);
	  printDebug1("End:uint8_t getValue C6 =>%d",C[6]);
		printDebug1("End:uint8_t getValue D1_1024 =>%d",D1);
    printDebug1("End:uint8_t getValue D2_1024 =>%d",D2);
	/*---------------------------------------------------------------------*/
	//printDebug1("End:uint8_t getValue D1_4096 =>%d",D1_4096);
  //printDebug1("End:uint8_t getValue D2_4096 =>%d",D2_4096);
		
	//printDebug1("End:uint8_t getValue D1_2048 =>%d",D1_2048);
	//printDebug1("End:uint8_t getValue D2_2048 =>%d",D2_2048);
		
	//printDebug1("End:uint8_t getValue D1_1024 =>%d",D1_1024);
	//printDebug1("End:uint8_t getValue D2_1024 =>%d",D2_1024);
		
	//printDebug1("End:uint8_t getValue D1_512 =>%d",D1_512);
	//printDebug1("End:uint8_t getValue D2_512 =>%d",D2_512);
		
	//printDebug1("End:uint8_t getValue D1_256 =>%d",D1_256);
	//printDebug1("End:uint8_t getValue D2_256 =>%d",D2_256);
	/*-----------------------------------------------------------------------*/
	
		printDebugF1("End: getValue dT =>%f",dT);
		printDebugF1("End: getValue OFF =>%f",OFF);
	  printDebugF1("End: getValue SENS =>%f",SENS);
	 
		printDebugF1("End: getValue T =>%f",T);
		printDebugF1("End: getValue P =>%f",P);
		// place to use P, T, put them on LCD, send them trough RS232 interface...
 return P;
} 
float getValueTemperature(void){
	return T;
}





// Stores all of the bmp085's calibration values into global variables
// Calibration values are required to calculate temp and pressure
// This function should be called at the beginning of the program
void bmp085Calibration(void)
{
	 printDebug("START uint8_t bmp085Calibration"); 
  ac1 = bmp085ReadInt(0xAA);
  ac2 = bmp085ReadInt(0xAC);
  ac3 = bmp085ReadInt(0xAE);
	
  ac4 = bmp085ReadInt(0xB0);
  ac5 = bmp085ReadInt(0xB2);
  ac6 = bmp085ReadInt(0xB4);
  b1 = bmp085ReadInt(0xB6);
  b2 = bmp085ReadInt(0xB8);
  mb = bmp085ReadInt(0xBA);
  mc = bmp085ReadInt(0xBC);
  md = bmp085ReadInt(0xBE);
	printDebug("END uint8_t bmp085Calibration"); 
	//
}

// Calculate temperature given ut.
// Value returned will be in units of 0.1 deg C
short bmp085GetTemperature(unsigned int ut)
{
  long x1, x2;
  
  x1 = (((long)ut - (long)ac6)*(long)ac5) >> 15;
  x2 = ((long)mc << 11)/(x1 + md);
  b5 = x1 + x2;

  return ((b5 + 8)>>4);  
}

// Calculate pressure given up
// calibration values must be known
// b5 is also required so bmp085GetTemperature(...) must be called first.
// Value returned will be pressure in units of Pa.
long bmp085GetPressure(unsigned long up)
{
  long x1, x2, x3, b3, b6, p;
  unsigned long b4, b7;
  
  b6 = b5 - 4000;
  // Calculate B3
  x1 = (b2 * (b6 * b6)>>12)>>11;
  x2 = (ac2 * b6)>>11;
  x3 = x1 + x2;
  b3 = (((((long)ac1)*4 + x3)<<OSS) + 2)>>2;
  
  // Calculate B4
  x1 = (ac3 * b6)>>13;
  x2 = (b1 * ((b6 * b6)>>12))>>16;
  x3 = ((x1 + x2) + 2)>>2;
  b4 = (ac4 * (unsigned long)(x3 + 32768))>>15;
  
  b7 = ((unsigned long)(up - b3) * (50000>>OSS));
  if (b7 < 0x80000000)
    p = (b7<<1)/b4;
  else
    p = (b7/b4)<<1;
    
  x1 = (p>>8) * (p>>8);
  x1 = (x1 * 3038)>>16;
  x2 = (-7357 * p)>>16;
  p += (x1 + x2 + 3791)>>4;
  
  return p;
}

// Read 1 byte from the BMP085 at 'address'
char bmp085Read(unsigned char address)
{
  unsigned char data;
  
  i2c_write(BMP085_ADDRESS,address);
	i2c_start();
	i2c_address_direction(BMP085_ADDRESS << 1, I2C_Direction_Receiver);
	data = (unsigned char )i2c_receive_nack();
	i2c_stop();

  return data;
}

// Read 2 bytes from the BMP085
// First byte will be from 'address'
// Second byte will be from 'address'+1
int bmp085ReadInt(unsigned char address)
{
  unsigned char msb, lsb;
  
  i2c_write(BMP085_ADDRESS,address);

	i2c_start();
	i2c_address_direction(BMP085_ADDRESS << 1, I2C_Direction_Receiver);
	msb=i2c_receive_ack();
	lsb=i2c_receive_nack();
	i2c_stop();
  return (int) msb<<8 | lsb;
}

// Read the uncompensated temperature value
unsigned int bmp085ReadUT(void)
{
  unsigned int ut;
  // Write 0x2E into Register 0xF4
  // This requests a temperature reading
  Mpu_Write(BMP085_ADDRESS,0xF4,0x2E);
  // Wait at least 4.5ms
  delay(5);
  
  // Read two bytes from registers 0xF6 and 0xF7
  ut = bmp085ReadInt(0xF6);
  return ut;
}

// Read the uncompensated pressure value
unsigned long bmp085ReadUP(void)
{
  unsigned char msb, lsb, xlsb;
  unsigned long up = 0;
  // Write 0x34+(OSS<<6) into register 0xF4
  // Request a pressure reading w/ oversampling setting
  Mpu_Write(BMP085_ADDRESS,0xF4,0x34 + (OSS<<6));
  // Wait for conversion, delay time dependent on OSS
  delay(2 + (3<<OSS));
  // Read register 0xF6 (MSB), 0xF7 (LSB), and 0xF8 (XLSB)
  i2c_write(BMP085_ADDRESS,0xF6);
	i2c_start();
	i2c_address_direction(BMP085_ADDRESS << 1, I2C_Direction_Receiver);
	msb=i2c_receive_ack();
	lsb=i2c_receive_ack();
	xlsb= i2c_receive_nack();
	i2c_stop();
  up = (((unsigned long) msb << 16) | ((unsigned long) lsb << 8) | (unsigned long) xlsb) >> (8-OSS);
  return up;
}

float getDataPressureSensorBM085(void)
{int t;
	
  temperature = bmp085GetTemperature(bmp085ReadUT());
	printDebug1("End:uint8_t bmp085GetTemperature=>%d",temperature); 
  pressure = bmp085GetPressure(bmp085ReadUP());
	printDebug1("End:uint8_t bmp085GetPressure=>%f",pressure); 
  altitude = (float)44330 * (1 - pow(((float) pressure/p0), 0.190295));
	printDebugF1("End:uint8_t getDataPressureSensor=>%f",altitude); 
	for(t=0;t<1680000000;t++);
}