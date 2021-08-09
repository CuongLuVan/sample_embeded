#include "MPU_6050.h"
#include "i2c_mpu_6050.h"
char dis[7];

void convert(int temp_data)
{ //temp_data/=60;
   if(temp_data<0)               //bit dau
   {
      temp_data=-temp_data;
      dis[0]='-';
   }
   else dis[0]='+';
	  dis[1] =temp_data/10000+0x30;    //lay so hang chuc nghin
   temp_data=temp_data%10000; 
	  dis[2] =temp_data/10000+0x30;    //lay so hang nghin
   temp_data=temp_data%1000; 
   dis[3] =temp_data/100+0x30;    //lay so hang tram
   temp_data=temp_data%100;     
   dis[4] =temp_data/10+0x30;    // lay so hang chuc
   temp_data=temp_data%10;      
   dis[5] =temp_data+0x30;      // lay so hang don vi 
	  dis[6] ='\0';    //lay so hang tram
}

void Display_Value(int value, unsigned char x, unsigned char y)
{ 
   convert(value);
  // print1(dis,x,y,0);
}
void Mpu6050_Init()
   {
   Mpu6050_Write(PWR_MGMT_1, 0x00);   
   Mpu6050_Write(SMPLRT_DIV, 0x07);
   Mpu6050_Write(CONFIG, 0x06);
   Mpu6050_Write(GYRO_CONFIG, 0x18);  
   Mpu6050_Write(ACCEL_CONFIG, 0x01); //old: 0x01
   }
unsigned int GetData(unsigned char address)
{
   char H,L;
   H=Mpu6050_Read(address);
   L=Mpu6050_Read(address+1);
   return (H<<8)+L;   
}
unsigned char Mpu6050_Read(unsigned char address)
   {
   char AckTemp=1;
   unsigned char Data;
   I2C_Start();
   I2C_Write(mpu6050);
   AckTemp=I2C_CheckAck();
   I2C_Write(address);
   AckTemp=I2C_CheckAck();
   I2C_Start();
   I2C_Write(mpu6050+1);
   AckTemp=I2C_CheckAck();
   Data=I2C_Read();
   AckTemp=I2C_CheckAck();
   I2C_Stop();
   return Data;
   }
void Mpu6050_Write(unsigned char address,unsigned char Data)
   {
   char AckTemp=1;
   I2C_Start();
   I2C_Write(mpu6050);
   AckTemp=I2C_CheckAck();
   I2C_Write(address);                   
   AckTemp=I2C_CheckAck();
   I2C_Write(Data);                 
   AckTemp=I2C_CheckAck();
   I2C_Stop();
   }

