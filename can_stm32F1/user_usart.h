/*****************************************************************************
  *Ten Tep          :     user_usart.h
  *Ngay             :     19/06/2014
  *Tac Gia          :     MinhHa R&D Team
  *Cong Ty          :     MinhHaGroup
  *Webside          :     mcu.banlinhkien.vn
  *Phien Ban        :     V1.0
  *Tom Tat          :     Khai bao cac ham cau hinh USART cho STM32F103x8
  ******************************************************************************/

#ifndef __USER_USART_H
#define __USER_USART_H    19062014

#include "main.h"

/*******************************************************************************
Noi Dung    : Cau hinh USARTx.
Tham Bien   : USARTx : Cac bo USART: USART1, USART2, USART3.
Tra Ve      : Khong.
********************************************************************************/

void USARTx_Configuration(USART_TypeDef* USARTx);

/*******************************************************************************
Noi Dung    : Gui mot ky tu.
Tham Bien   : USARTx : Cac bo USART: USART1, USART2, USART3.
              Data   : Ky tu can gui.
Tra Ve      : Khong.
********************************************************************************/

void USARTx_SendChar(USART_TypeDef* USARTx, uint8_t Data);

/*******************************************************************************
Noi Dung    : Gui mot chuoi ky tu.
Tham Bien   : USARTx : Cac bo USART: USART1, USART2, USART3.
              *Str   : Chuoi ky tu can gui
Tra Ve      : Khong.
********************************************************************************/

void USARTx_SendString(USART_TypeDef* USARTx, uint8_t *Str);

/*******************************************************************************
Noi Dung    : Nhan mot ky tu.
Tham Bien   : USARTx : Cac bo USART: USART1, USART2, USART3.
Tra Ve      : Ky tu nhan duoc.
********************************************************************************/

uint8_t USARTx_GetChar(USART_TypeDef* USARTx);
//void USARTx_GetString (USART_TypeDef* USARTx, uint8_t *Str);

#endif
/*------------------------------KET THUC FILE-------------------------------
 ______________________________MinhHa R&D Team______________________________*/

