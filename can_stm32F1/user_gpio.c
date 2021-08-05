/*****************************************************************************
  *Ten Tep          :     user_gpio.h
  *Ngay             :     16/06/2014
  *Tac Gia          :     MinhHa R&D Team
  *Cong Ty          :     MinhHaGroup
  *Webside          :     mcu.banlinhkien.vn
  *Phien Ban        :     V1.0
  *Tom Tat          :     Khai bao cac ham cau hinh GPIO cho STM32F103x8
  ******************************************************************************
  * Chu Y:
  *		- GPIO_Mode: OUTPUT
  *			GPIO_Mode_Out_PP		--> Output Push Pull
  *			GPIO_Mode_Out_OD		--> Output Open Drain
  *			GPIO_Mode_AF_OD			--> Alternate Function Open Drain
  *			GPIO_Mode_AF_PP			--> Alternate Function Push Pull
  *		- GPIO_Mode: INPUT
  *			GPIO_Mode_AIN			--> Input Analog
  *			GPIO_Mode_IN_FLOATING	--> Input Floating
  *			GPIO_Mode_IPD			--> Input Pull Down
  *			GPIO_Mode_IPU			--> Input Pull Up
  *		- Neu su dung Alternate Function(USART, TIMER, I2C,SPI...) ta phai enable clock cho AFIO:
  *			RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  *			Vi Du: Ta cau hinh GPIO su dung USART1
  *				- Enable clock GPIOA	: 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
  *				- Enable clock AFIO		:	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  *				- Cau hinh PIN TX		:	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	         		
  *											GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  *											GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  *											GPIO_Init(GPIOA, &GPIO_InitStructure);
  *				- Cau hinh PIN RX		:	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  *											GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  *											GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  *											GPIO_Init(GPIOA, &GPIO_InitStructure);			
  ******************************************************************************
**/	
	
#include "user_gpio.h"
#if (__USER_GPIO_H !=16062014)
    #error "Include Sai #File user_gpio.h"
#endif

#define    	LED1    PINB_12
#define    	LED2    PINB_13
#define 		BUTTON1 	PINA_6
#define 		BUTTON2 	PINA_7

/*******************************************************************************
Noi Dung    : Cau hinh GPIO.
Tham Bien   : Khong.
Tra Ve      : Khong.
********************************************************************************/

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);		
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
/********************************* PORTA *************************************/
/*________________________________ OUTPUT ___________________________________*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
/*________________________________ INPUT ____________________________________*/

/********************************* PORTB *************************************/
/*________________________________ OUTPUT ___________________________________*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
/*________________________________ INPUT ____________________________________*/

/********************************* PORTC *************************************/
/*________________________________ OUTPUT ___________________________________*/
/*________________________________ INPUT ____________________________________*/

/********************************* PORTD *************************************/
/*________________________________ OUTPUT ___________________________________*/
/*________________________________ INPUT ____________________________________*/

/********************************* PORTE *************************************/
/*________________________________ OUTPUT ___________________________________*/
/*________________________________ INPUT ____________________________________*/

/********************************* PORTF *************************************/
/*________________________________ OUTPUT ___________________________________*/
/*________________________________ INPUT ____________________________________*/

/********************************* PORTG *************************************/
/*________________________________ OUTPUT ___________________________________*/
/*________________________________ INPUT ____________________________________*/
}

/*------------------------------KET THUC FILE-------------------------------
 ______________________________MinhHa R&D Team______________________________*/

