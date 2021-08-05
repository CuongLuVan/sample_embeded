/*****************************************************************************
  *Ten Tep          :     user_usart.c
  *Ngay             :     19/06/2014
  *Tac Gia          :     MinhHa R&D Team
  *Cong Ty          :     MinhHaGroup
  *Webside          :     mcu.banlinhkien.vn
  *Phien Ban        :     V1.0
  *Tom Tat          :     Dinh nghia cac ham cau hinh USART cho STM32F103x8
  ******************************************************************************/
  
#include "user_usart.h"
#if (__USER_USART_H!=19062014)
    #error "Include Sai File user_usart.h"
#endif

/*******************************************************************************
Noi Dung    : Cau hinh USARTx.
Tham Bien   : USARTx : Cac bo USART: USART1, USART2, USART3.
Tra Ve      : Khong.
********************************************************************************/

void USARTx_Configuration(USART_TypeDef* USARTx)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);		
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
/********************************* PORTA *************************************/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
/*________________________________ OUTPUT ___________________________________*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;    // TX - USART1	 	         		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
/*________________________________ INPUT ____________________________________*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;    // RX - USART1	         		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	USART_DeInit(USART1);
	
	USART_InitStructure.USART_BaudRate = 9600;    // Cau hinh BaudRate
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;    // Cau hinh so Bit du lieu trong 1 khung truyen/nhan
	                                                               // USART_WordLength_8b
																   // USART_WordLength_9b 
	USART_InitStructure.USART_StopBits = USART_StopBits_1;    // Cau hinh so Bit STOP trong khung truyen
	                                                          // USART_StopBits_1
															  // USART_StopBits_0_5
															  // USART_StopBits_2
															  // USART_StopBits_1_5
	USART_InitStructure.USART_Parity = USART_Parity_No;    // Cau hinh su dung che do Parity
	                                                       // USART_Parity_No
														   // USART_Parity_Even
														   // USART_Parity_Odd
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;    // Cau hinh che do dieu khien theo luong
	                                                                                   // USART_HardwareFlowControl_None
																					   // USART_HardwareFlowControl_RTS
																					   // USART_HardwareFlowControl_CTS
																					   // USART_HardwareFlowControl_RTS_CTS
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;    // Cau hinh che do truyen nhan
	                                                                   // USART_Mode_Rx
																	   // USART_Mode_Tx
	USART_Init(USARTx, &USART_InitStructure);    // Cau hinh USART1
	
	//USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);    // Xay ra ngat khi thanh ghi du lieu nhan cua USART1 day       
	//USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);     // Xay ra ngat khi thanh ghi du lieu truyen cua USART1 trong  
	
	USART_Cmd(USARTx, ENABLE);                   // Kich hoat USART1																                                          	
}

/*******************************************************************************
Noi Dung    : Gui mot ky tu.
Tham Bien   : USARTx : Cac bo USART: USART1, USART2, USART3.
              Data   : Ky tu can gui.
Tra Ve      : Khong.
********************************************************************************/

void USARTx_SendChar(USART_TypeDef* USARTx, uint8_t Data)
{
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
	USART_SendData(USARTx,Data);
}

/*******************************************************************************
Noi Dung    : Gui mot chuoi ky tu.
Tham Bien   : USARTx : Cac bo USART: USART1, USART2, USART3.
              *Str   : Chuoi ky tu can gui
Tra Ve      : Khong.
********************************************************************************/

void USARTx_SendString(USART_TypeDef* USARTx, uint8_t *Str)
{
	while(*Str)
	{
		USARTx_SendChar(USARTx,*Str); 
		Str++;
	}
}

/*******************************************************************************
Noi Dung    : Nhan mot ky tu.
Tham Bien   : USARTx : Cac bo USART: USART1, USART2, USART3.
Tra Ve      : Ky tu nhan duoc.
********************************************************************************/

uint8_t USARTx_GetChar(USART_TypeDef* USARTx)
{
	uint8_t Data;
	while(USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET);
	Data = (uint8_t) USART_ReceiveData(USARTx);
	return Data;
}


