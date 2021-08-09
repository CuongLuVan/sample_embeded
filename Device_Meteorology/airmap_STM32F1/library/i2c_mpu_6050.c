#include "i2c_mpu_6050.h"
#define SCL_MPU GPIO_Pin_6
#define SDA_MPU GPIO_Pin_7
#define SCL_PORT GPIOB
#define SDA_PORT GPIOB
#define PRESSURESENSOR_ADRESS  0xEC// 0x76  // 1110 1100 =>
void I2C_Delay(unsigned int time)
{ int k;
	while(time){
		for(k=2;k>0;k--);
	time--;}
}
void i2c_datasumit(void){
GPIO_InitTypeDef GPIO_InitStruct;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	/*Configure GPIO pin */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	//GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}
void i2c_dataout(void){
GPIO_InitTypeDef GPIO_InitStruct;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	/*Configure GPIO pin */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}


void I2C_MPUInit()
{ GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
	/*Configure GPIO pin */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
//	SCL=1;
	GPIO_SetBits(SCL_PORT,SCL_MPU);
	I2C_Delay(I2C_DELAY);
	//SDA=1;
		GPIO_SetBits(SDA_PORT,SDA_MPU);
	I2C_Delay(I2C_DELAY);
}
void I2C_Start()
{i2c_dataout();
	//SDA=1; 
  	//SCL=1; 
		GPIO_SetBits(SDA_PORT,SDA_MPU);
		GPIO_SetBits(SCL_PORT,SCL_MPU);
  	I2C_Delay(I2C_DELAY);
  //	SDA=0; 
		GPIO_ResetBits(SDA_PORT,SDA_MPU);
  	I2C_Delay(I2C_DELAY);
  	//SCL=0;
	GPIO_ResetBits(SCL_PORT,SCL_MPU);
  	I2C_Delay(I2C_DELAY);
}
void I2C_Stop()
{	i2c_dataout();
	//SDA=0;
  	//SCL=1;
	GPIO_ResetBits(SDA_PORT,SDA_MPU);
	GPIO_SetBits(SCL_PORT,SCL_MPU);
  	I2C_Delay(I2C_DELAY);
  	//SDA=1;
	GPIO_SetBits(SDA_PORT,SDA_MPU);
  	I2C_Delay(I2C_DELAY);
  	//SCL=0;
	GPIO_ResetBits(SCL_PORT,SCL_MPU);
  	I2C_Delay(I2C_DELAY);
}
unsigned char I2C_CheckAck(void)
{
	unsigned char ack=0;
  	//SDA=1;
  	//SCL=1;
	i2c_datasumit();
	GPIO_SetBits(SDA_PORT,SDA_MPU);
	GPIO_SetBits(SCL_PORT,SCL_MPU);
  	I2C_Delay(I2C_DELAY/2);
	 if (GPIO_ReadInputDataBit(SDA_PORT,SDA_MPU))
  	ack=1; 
  	I2C_Delay(I2C_DELAY/2);
  //	SCL=0;
	GPIO_ResetBits(SCL_PORT,SCL_MPU);
  	I2C_Delay(I2C_DELAY);
  	if(ack==1) return 0; 
  	return 1;
}
void I2C_Write(unsigned char Data)
{
unsigned char i;
	i2c_dataout();
  	for(i=0;i<8;i++)
    {
			if(((Data<<i)&0x80)) GPIO_SetBits(SDA_PORT,SDA_MPU);
			else GPIO_ResetBits(SDA_PORT,SDA_MPU);
			
	//	SCL=1;
				GPIO_SetBits(SCL_PORT,SCL_MPU);
		I2C_Delay(I2C_DELAY);
				GPIO_ResetBits(SCL_PORT,SCL_MPU);
		//SCL=0;
		I2C_Delay(I2C_DELAY);
			
	}
}
unsigned char I2C_Read(void)
{
  	unsigned char I2C_data=0,i,temp;
i2c_datasumit();  
	for(i=0;i<8;i++)
    {
    	//SDA=1;    
      	//SCL=1; 
	GPIO_SetBits(SCL_PORT,SCL_MPU);
	GPIO_SetBits(SDA_PORT,SDA_MPU);			
      	I2C_Delay(120);
   if (GPIO_ReadInputDataBit(SDA_PORT,SDA_MPU))  temp=1; else temp=0;
      	I2C_Delay(120);
      //	SCL=0;
				GPIO_ResetBits(SCL_PORT,SCL_MPU);
      	if(temp==1)
       	{
         	I2C_data=I2C_data<<1;
         	I2C_data=I2C_data|0x01;
       	}
      	else
        	I2C_data=I2C_data<<1;
    }
    return I2C_data;
}


unsigned char Mpu6050_Read(unsigned char address)
{
   char AckTemp=1;
   unsigned char Data;
   I2C_Start();
   //I2C_Write(PRESSURESENSOR_ADRESS);
   //AckTemp=I2C_CheckAck();
   //I2C_Write(address);
   //AckTemp=I2C_CheckAck();
   //I2C_Start();
   I2C_Write(PRESSURESENSOR_ADRESS+1);
   AckTemp=I2C_CheckAck();
   Data=I2C_Read();
   AckTemp=I2C_CheckAck();
   I2C_Stop();
   return Data;
}


void Mpu6050_Write(unsigned char Data)
{
   char AckTemp=1;
   I2C_Start();
   I2C_Write(PRESSURESENSOR_ADRESS);
   AckTemp=I2C_CheckAck();
   //I2C_Write(address);                   
   //AckTemp=I2C_CheckAck();
   I2C_Write(Data);                 
   AckTemp=I2C_CheckAck();
   I2C_Stop();
}


