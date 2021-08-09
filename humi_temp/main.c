
#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_can.h"
#include "stm32f10x_cec.h"
#include "stm32f10x_crc.h"
#include "stm32f10x_dbgmcu.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_flash.h"
#include "stm32f10x_fsmc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_iwdg.h"
#include "stm32f10x_pwr.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_rtc.h"
#include "stm32f10x_sdio.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_tim.h"
#define SYSCLK_FREQ_HSE  SYSCLK_FREQ_72MHz
extern __IO uint32_t TimeDisplay;
extern uint16_t hoatdongphim;
extern uint8_t phim;
int cuca;

int main(void)
{
	int uouo,uoui;
  
	setup_Nokia();
	delay_ms(1000);
  setup_Fist();
	delay_ms(40000);
	GPIO_SetBits(GPIOA,GPIO_Pin_12);
	setup_nutbam(); 
	while (1)
  {
		GPIO_SetBits(GPIOA,GPIO_Pin_12);
    action_device();
		//quyetdinh();
		delay_ms(2000);	
		GPIO_ResetBits(GPIOA,GPIO_Pin_12);	
		delay_ms(2000);
		
}
}


void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}




