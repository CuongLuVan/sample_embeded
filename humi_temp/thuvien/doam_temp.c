//#include "main.h"
//#include <msp430g2553.h>
#include <stdio.h>
#include "stm32f10x_gpio.h"

// Khai bao chan cho LCD16x2 - PORT1
// Khai bao cho DHT11 - PORT2
#define DHT_DDR_DATA	BIT0
#define DHT_DATA_OUT	BIT0
#define DHT_DATA_IN		BIT0

// Khai bao Speak - PORT2
#define SPEAK			BIT1

// Khai bao MQ2 - PORT2
#define MQ2				BIT2

#define DHT_ER       0
#define DHT_OK       1

/*******************************************************************************
Noi Dung    :   Doc gia tri nhiet do, do am tu DHT.
Tham Bien   :   *tem:    con tro luu tru gia tri nhiet do.
                *humi:   con tro luu tru gia tri do am.
Tra Ve      :   - DHT_OK:   Neu do nhiet do,do am thanh cong.
                - DHT_ER:   Neu do nhiet do, do am xay ra loi.
 *******************************************************************************/
	uint8_t temp;
	uint8_t humi;
void DHT11_init_input(void){
GPIO_InitTypeDef GPIO_InitStruct;

	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	/*Configure GPIO pin */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9; 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct); //chuadat

}
void DHT11_init_output(void){
GPIO_InitTypeDef kieu;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	  kieu.GPIO_Pin=GPIO_Pin_9;
	  kieu.GPIO_Speed=GPIO_Speed_50MHz;
	  kieu.GPIO_Mode=GPIO_Mode_Out_PP;
        GPIO_Init(GPIOC,&kieu);

}

_delay_cycles(uint32_t count){
uint16_t dem;
while(count--){
for(dem=0;dem<100;dem++);
}

}

uint8_t DHT_GetTemHumi (uint8_t *tem,uint8_t *humi)
{
    uint8_t buffer[5]={0,0,0,0,0};
    uint8_t ii,i,checksum;

//	P2DIR |= DHT_DDR_DATA;
	//P2OUT |= DHT_DATA_OUT;
	//delay_us(60);
	_delay_cycles(60);
    //P2OUT &= ~DHT_DATA_OUT;
DHT11_init_output();
GPIO_ResetBits(GPIOA,GPIO_Pin_1);
    //delay_ms(25); // it nhat 18ms
    _delay_cycles(25000);
  //  P2OUT |= DHT_DATA_OUT;

GPIO_SetBits(GPIOA,GPIO_Pin_1);
DHT11_init_input();
    //P2DIR &= ~DHT_DDR_DATA;
    //delay_us(60);
    _delay_cycles(60);

    //if(P2IN & DHT_DATA_IN)
		if((GPIOA->IDR & GPIO_Pin_1))	return DHT_ER ;
    else while(!(GPIOA->IDR & GPIO_Pin_1));	//Doi DaTa len 1
    //delay_us(60);
    _delay_cycles(60);
    if(!(GPIOA->IDR & GPIO_Pin_1))return DHT_ER;
    else while((GPIOA->IDR & GPIO_Pin_1));	 //Doi Data ve 0
    //Bat dau doc du lieu
    for(i=0;i<5;i++)
    {
        for(ii=0;ii<8;ii++)
        {
        while(!((GPIOA->IDR & GPIO_Pin_1)));//Doi Data len 1
        //delay_us(50);
        _delay_cycles(50);
        if((GPIOA->IDR & GPIO_Pin_1))
            {
            buffer[i]|=(1<<(7-ii));
            while((GPIOA->IDR & GPIO_Pin_1));//Doi Data xuong 0
            }
        }
    }
	//Tinh toan check sum
    checksum=buffer[0]+buffer[1]+buffer[2]+buffer[3];
	//Kiem tra check sum
    if((checksum)!=buffer[4])return DHT_ER;
	//Lay du lieu
    *tem  =   buffer[2];
    *humi =   buffer[0];
    return DHT_OK;
}
void show_all_doam_temp(void){

DHT_GetTemHumi(&temp,&humi);
}

/*
void  main(void)
{
	uint8_t temp=2;
	uint8_t humi=12;
	uint8_t str[16];
	WDTCTL = WDTPW + WDTHOLD;  	// Stop watchdog timer, Tan so Clock 1MHz
  
	P1DIR = 0xff;	// Cau hinh PORT1 là Output        	
	P1OUT = 0x00;	
	
	P2DIR |= BIT0|BIT1;	// Cau hinh PORT2.0, PORT2.1 là Output
	P2DIR &= ~BIT2;		// Cau hinh PORT2.2 là Input 
    P2REN &= ~BIT2; 		// Cau hinh khong tro treo cho PORT2.2
      		
	Buzz_Off();
	
	LCD_Init ();
	LCD_Gotoxy(0,0);
	sprintf(str,"   PROJECT II   ");
	LCD_Puts(str);	
	_delay_cycles(2000000);	// 2s
	LCD_Clear();
	while(1)
	{
		if(DHT_GetTemHumi (&temp,&humi))
		{
			sprintf(str,"Temp: %d%cC",temp,'\xdf');
			LCD_Gotoxy(0,0);
			LCD_Puts(str);
			sprintf(str,"Humi: %d%c",humi,'%');
			LCD_Gotoxy(0,1);
			LCD_Puts(str);				
		}
		if(P2IN & MQ2)Buzz_On();
		else Buzz_Off();
	}
}
*/