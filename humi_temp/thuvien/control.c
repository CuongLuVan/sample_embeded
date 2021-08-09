
#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_bkp.h"
#include "stm32f10x_can.h"
#include "stm32f10x_cec.h"
#include "stm32f10x_crc.h"
#include "stm32f10x_dac.h"
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
#include "stm32f10x_usart.h"
#include "stm32f10x_wwdg.h"

extern uint8_t phim,luutru,dem,dabam,luuphim;
extern uint16_t hoatdongphim;
extern uint8_t temp,temph;
extern	uint8_t humi;
extern uint32_t timer,timerset,timercount;
extern uint16_t doam,light,count_history,auto_doam,auto_doamdat,auto_temp,auto_light;
extern uint16_t time_second,time_mun,time_hour,time_set_mun,time_set_hour;
extern uint8_t  warning,water;
uint8_t canhbao,canhbao1; 
 extern uint16_t count_history;
 
uint16_t filter_old[5];
uint16_t filter_new[5];
uint16_t filter_set[5];
 
 void out_device_init(void){
	 
GPIO_InitTypeDef GPIO_InitStruct;
	/*Enable or disable the AHB1 peripheral clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	/*Configure GPIO pin */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;;
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	/*Configure GPIO pin */
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_10;
	  GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
        GPIO_Init(GPIOC,&GPIO_InitStruct);
	 GPIO_SetBits(GPIOC,GPIO_Pin_1);
	 	/*Configure GPIO pin */ 
   GPIO_ResetBits(GPIOC,GPIO_Pin_10);
	 GPIO_ResetBits(GPIOC,GPIO_Pin_0);
}
 
 
void setup_Fist(void){
	// setuplcd
	NOKIA5110_Init();
	NOKIA5110_Clear();
	NOKIA5110_GotoXY(0,0);
  NOKIA5110_Puts("hello"); 
	NOKIA5110_GotoXY(0,1);
  NOKIA5110_Puts("hello"); 
	NOKIA5110_GotoXY(0,2);
  NOKIA5110_Puts("hello"); 
	NOKIA5110_GotoXY(0,3);
  NOKIA5110_Puts("hello"); 

// doc nhiet do va do am
	//show_all_doam_temp();
	// setup adc
	setup_ADC();
	setup_nutbam();
	show_for_digit(docgiatriadc0()*2);	
	//mx_sd_config();
	
}

void lowpower(void){
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
                         RCC_APB2Periph_GPIOE, DISABLE);  

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
//	rcc_set_prescaler(RCC_PRESCALER_AHB, RCC_AHB_SYSCLK_DIV_256); //slows down cpu and reduces power

   PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
	


//rcc_set_prescaler(RCC_PRESCALER_AHB, RCC_AHB_SYSCLK_DIV_1); /normal cpu speed

}

void action(void){
uint8_t i;
uint8_t _lowpower=0;	
		for(i=0;i<5;i++){
		if(filter_new[i]>filter_set[i]) {
				filter_old[i]=0;
			_lowpower=1;
			}else {
			if(filter_old[i]>300){ filter_old[i]++;
				_lowpower=1;
			}
				else filter_old[i]=0;
			}
	}

	
if(hoatdongphim==0){
	GPIO_ResetBits(GPIOC,GPIO_Pin_1);
  // show_all_doam_temp();
	if(auto_temp!=0) { if(temp>temph) canhbao=1;} // keogiem anh sang
	if(auto_doam!=0) { if(humi>doam) canhbao1=2; }// bom nuoc
if (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)==0) canhbao1=2; //bom nuoc
if (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)==0) canhbao1=0; // ngung bom
GPIO_SetBits(GPIOC,GPIO_Pin_1);
interface();
if(auto_light!=0) if(docgiatriadc0()>light) canhbao=1;

}

	if(1==_lowpower){
		lowpower();
	}
}




void quyetdinh(void){
if(canhbao!=0){
		if(canhbao==1){
				GPIO_SetBits(GPIOC,GPIO_Pin_10);// keogiem anh sang
				}
if(canhbao1==1){
				GPIO_SetBits(GPIOC,GPIO_Pin_1);// bomnuoc
				}
if(warning!=0) {
GPIO_SetBits(GPIOC,GPIO_Pin_13);//
}

}else{
		GPIO_ResetBits(GPIOC,GPIO_Pin_10);//ko keo giem anh sang
    GPIO_ResetBits(GPIOC,GPIO_Pin_1);//ko keo giem anh sang
      GPIO_ResetBits(GPIOC,GPIO_Pin_13);//
}

}


void action_device(void){
xacdinnh_chedo();
action();
quyetdinh();
}

