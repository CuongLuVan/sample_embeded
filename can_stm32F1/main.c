/**
  ******************************************************************************
  * @file    USART/Synchronous/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "main.h"
uint8_t charRX;
uint8_t String[32];
CanTxMsg TxCAN_USART;
CanRxMsg RxCAN_USART;

void  string_config(void)
{
		int i;
	for (i=0;i<32;i++)
	{
			String[i]=0;
	}
	
}

void delay_user(int sec)
{
		int k,m;
	for (m=0;m<sec;m++)
	{
		for (k=0;k<16000;k++);
	}
}

int main(void)
{
  /********************************* SYSTEM *************************************/
	SystemInit();
	USARTx_Configuration(USART1);
	
	GPIO_Configuration();
	USARTx_SendString(USART1,(uint8_t*)"Giao tiep CAN STM32F103 \r\n");
/********************************* USER FUNCTION *************************************/
	delay_init(168);
	string_config();
	USARTx_SendString(USART1,(uint8_t*)"Giao tiep CAN STM32F103 \r\n");
/********************************* CODE TX CAN *************************************/	
		NVIC_Configuration();
/*________________________________ CAN ___________________________________*/		
	CAN_Configuration	();
/*________________________________ GPIO ___________________________________*/

//	TxCAN_USART.StdId = 0x321;
//  TxCAN_USART.ExtId = 0x01;
//  TxCAN_USART.RTR = CAN_RTR_DATA;
//  TxCAN_USART.IDE = CAN_ID_STD;
//  TxCAN_USART.DLC = 8;
//	
	TxCAN_USART.Data[0]='V';
	TxCAN_USART.Data[1]='u';
	TxCAN_USART.Data[2]=' ';
	TxCAN_USART.Data[3]='H';
	TxCAN_USART.Data[4]='o';
	TxCAN_USART.Data[5]='a';
	TxCAN_USART.Data[6]='n';
	TxCAN_USART.Data[7]='g';
	
	
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
  while (1)
  {
//		charRX= USARTx_GetChar(USART1);
//		TxCAN_USART.Data[0] = charRX;
//		CAN_Transmit(CAN1, &TxCAN_USART);
//		Delay();
//		Init_RxMes(&RxCAN_USART);
//		CAN_Receive(CAN1, 1, &RxCAN_USART);
//		USARTx_SendChar(USART1,(uint8_t)&RxCAN_USART);
		delay_user(1800);
		USARTx_SendString(USART1,(uint8_t*)"Request USART\r\n");
			CAN_Receive(CAN1, CAN_FIFO0, &RxCAN_USART);
    USARTx_SendChar(USART1,RxCAN_USART.Data[0]);
//			CAN_Transmit(CAN1, &TxCAN_USART);
		}
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
