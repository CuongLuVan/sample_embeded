#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#define ACTION_UP 1
#define ACTION_DOWN 2
#define ACTION_OK 3
#define ACTION_HIGHTUP 4
#define ACTION_LOWDOWN 5
#define ACTION_NEXT 6
#define ACTION_MENU 7

#define GPIO_PIN_ACTION_UP GPIO_Pin_14
#define GPIO_PIN_ACTION_DOWN GPIO_Pin_15
#define GPIO_PIN_ACTION_OK GPIO_Pin_8
#define GPIO_PIN_ACTION_HIGHTUP GPIO_Pin_9
#define GPIO_PIN_ACTION_LOWDOWN GPIO_Pin_10
#define GPIO_PIN_ACTION_NEXT GPIO_Pin_11
#define GPIO_PIN_ACTION_MENU GPIO_Pin_12

#define GPIO_ACTION_UP GPIOB
#define GPIO_ACTION_DOWN GPIOB
#define GPIO_ACTION_OK GPIOA
#define GPIO_ACTION_HIGHTUP GPIOA
#define GPIO_ACTION_LOWDOWN GPIOA
#define GPIO_ACTION_NEXT GPIOA
#define GPIO_ACTION_MENU GPIOA

#define RCC_ACTION_UP RCC_APB2Periph_GPIOB
#define RCC_ACTION_DOWN RCC_APB2Periph_GPIOB
#define RCC_ACTION_OK RCC_APB2Periph_GPIOA
#define RCC_ACTION_HIGHTUP RCC_APB2Periph_GPIOA
#define RCC_ACTION_LOWDOWN RCC_APB2Periph_GPIOA
#define RCC_ACTION_NEXT RCC_APB2Periph_GPIOA
#define RCC_ACTION_MENU RCC_APB2Periph_GPIOA


uint8_t phim,luutru,dem,dabam,luuphim;
uint16_t hoatdongphim;


void  setup_nutbam(void){
GPIO_InitTypeDef GPIO_InitStruct;
hoatdongphim=0;
	/*Enable or disable the AHB1 peripheral clock */
  RCC_APB2PeriphClockCmd(RCC_ACTION_UP |RCC_ACTION_DOWN| RCC_ACTION_OK| RCC_ACTION_HIGHTUP
	|RCC_ACTION_LOWDOWN |RCC_ACTION_NEXT |RCC_ACTION_MENU, ENABLE);
	/*Configure GPIO pin */
	GPIO_InitStruct.GPIO_Pin = GPIO_PIN_ACTION_UP;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_ACTION_UP, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_PIN_ACTION_DOWN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_ACTION_UP, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_PIN_ACTION_OK;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_ACTION_UP, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_PIN_ACTION_HIGHTUP;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_ACTION_UP, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_PIN_ACTION_LOWDOWN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_ACTION_DOWN, &GPIO_InitStruct);	
	
	GPIO_InitStruct.GPIO_Pin = GPIO_PIN_ACTION_NEXT;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_ACTION_NEXT, &GPIO_InitStruct);	

	GPIO_InitStruct.GPIO_Pin = GPIO_PIN_ACTION_MENU;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_ACTION_MENU, &GPIO_InitStruct);	
}

#define GPIO_PIN_ACTION_UP GPIO_Pin_14
#define GPIO_PIN_ACTION_DOWN GPIO_Pin_15
#define GPIO_PIN_ACTION_OK GPIO_Pin_8
#define GPIO_PIN_ACTION_HIGHTUP GPIO_Pin_9
#define GPIO_PIN_ACTION_LOWDOWN GPIO_Pin_10
#define GPIO_PIN_ACTION_NEXT GPIO_Pin_11
#define GPIO_PIN_ACTION_MENU GPIO_Pin_12

void nutbam(void){
phim=0;
if (GPIO_ReadInputDataBit(GPIO_ACTION_UP,GPIO_PIN_ACTION_UP)== RESET) phim=ACTION_UP;
if (GPIO_ReadInputDataBit(GPIO_ACTION_DOWN,GPIO_PIN_ACTION_DOWN)== RESET) phim=ACTION_DOWN;
if (GPIO_ReadInputDataBit(GPIO_ACTION_OK,GPIO_PIN_ACTION_OK)== RESET) phim=ACTION_OK;
if (GPIO_ReadInputDataBit(GPIO_ACTION_NEXT,GPIO_PIN_ACTION_NEXT)== RESET) phim=ACTION_NEXT;
if (GPIO_ReadInputDataBit(GPIO_ACTION_HIGHTUP,GPIO_PIN_ACTION_HIGHTUP)== RESET) phim=ACTION_HIGHTUP;
if (GPIO_ReadInputDataBit(GPIO_ACTION_LOWDOWN,GPIO_PIN_ACTION_LOWNDOW)== RESET) phim=ACTION_LOWDOWN;	
if (GPIO_ReadInputDataBit(GPIO_ACTION_MENU,GPIO_PIN_ACTION_MENU)==RESET) phim=ACTION_MENU;
dem++;	
 if (luutru!=phim) {dem=0;}
       if ((phim!=0)&&(luuphim!=phim)&&(dem==20)) {dabam=1; luuphim=phim; dem=0;  }
       if (((dem<20)&(luuphim==phim))) {dem=0;}
       if ((phim==0)&&(dem>20)) {dem=0; luuphim=0xfe;}
luutru=phim;	
}

uint8_t xacdinnh_chedo(void){
uint32_t	chen;
nutbam();	
	NOKIA5110_GotoXY(0,4);
	show_for_digit(phim);
// dabam	
if (dabam!=0){
		NOKIA5110_GotoXY(0,5);
  NOKIA5110_Puts("ban da bam nut");
	switch(hoatdongphim)
		dabam=0;					 
}


return 0;
}


