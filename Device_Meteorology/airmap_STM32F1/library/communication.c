/*
file:  communication.c
description : manager all communicate of device
Create date : 19/2/2017
user cread : Lu Van Cuong
*/

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"

#include "debug.h" 
#include "communication.h"
#include "define.h"
#include "string.h"

void UART_SendChar(char ch) {
	while (!USART_GetFlagStatus(USART1,USART_FLAG_TC)); // wait for "Transmission Complete" flag cleared
	USART_SendData(USART1,(uint16_t)ch);
}

void setupUart(int BaudRate){
	GPIO_InitTypeDef port;
	USART_InitTypeDef uart;
	printDebug1("START setupLoraUart =>%d",BaudRate);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA| RCC_APB2Periph_USART1,ENABLE);

	// setting for uart 5V for Dust Sensor
	port.GPIO_Speed = GPIO_Speed_50MHz;
	port.GPIO_Mode = GPIO_Mode_AF_PP; // TX as AF with Push-Pull;
	port.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOA,&port);
	
	port.GPIO_Speed = GPIO_Speed_50MHz;
	port.GPIO_Mode = GPIO_Mode_IN_FLOATING; // RX as in without pull-up
	port.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA,&port);
	
	uart.USART_BaudRate = BaudRate;
	uart.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // No flow control
	uart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // RX+TX mode
	uart.USART_Parity = USART_Parity_No; // No parity check
	uart.USART_StopBits = USART_StopBits_1; // 1 stop bit
	uart.USART_WordLength = USART_WordLength_8b; // 8-bit frame
	USART_Init(USART1,&uart);
	USART_Cmd(USART1,ENABLE);
	UART_SendChar('b');
	printDebug1("END setupLoraUart =>%d",BaudRate);
}


