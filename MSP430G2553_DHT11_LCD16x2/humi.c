//#include "main.h"
#include <msp430g2553.h>
#include <stdio.h>
typedef   signed          char int8_t;
typedef   signed           int int16_t;
typedef   signed long      int int32_t;

/*   Kieu So Nguyen Khong Dau */
typedef   unsigned         char uint8_t;
typedef   unsigned           int  uint16_t;
typedef   unsigned long    int  uint32_t;
/*   Kieu So Thuc */
typedef   float            float32_t;


// Khai bao chan cho LCD16x2 - PORT1
#define LCD_RS			BIT0
#define LCD_RW			BIT1
#define LCD_EN			BIT2

// Khai bao cho DHT11 - PORT2
#define DHT_DDR_DATA	BIT0
#define DHT_DATA_OUT	BIT0
#define DHT_DATA_IN		BIT0

// Khai bao Speak - PORT2
#define SPEAK			BIT1

// Khai bao MQ2 - PORT2
#define MQ2				BIT2

#define DHT_ER       	0
#define DHT_OK       	1

void LCD_Enable(void);						//Tao xung Enable LCD
void LCD_Send4Bit(uint8_t   Data);		//Ham Gui 4 Bit Du Lieu Ra LCD
void LCD_SendCommand (uint8_t  command );// Ham Gui 1 Lenh Cho LCD
void LCD_Init ( void );								// Ham Khoi Tao LCD
void LCD_Gotoxy(uint8_t  x, uint8_t  y);	// Ham Thiet Lap Vi Tri Con Tro
void LCD_Clear();									// Ham Xoa Man Hinh LCD
void LCD_PutChar ( uint8_t  c );				// Ham Gui 1 Ki Tu Len LCD
void LCD_Puts (uint8_t  *s);					// Ham Gui 1 Chuoi Ki Tu Len LCD
void LCD_Enable(void)
{
	P1OUT |= LCD_EN;
	//delay_us(3);
	_delay_cycles(3);
	P1OUT &= ~LCD_EN;
	//delay_us(50);
	_delay_cycles(50);
}
//Ham Gui 4 Bit Du Lieu Ra LCD
void LCD_Send4Bit( uint8_t  Data )
{
	P1OUT &= 0x0F;
	P1OUT |= ((Data<<4)&0xF0);
}
// Ham Gui 1 Lenh Cho LCD
void LCD_SendCommand (uint8_t  command )
{
LCD_Send4Bit  ( command >>4 );   /* Gui 4 bit cao */
LCD_Enable () ;
LCD_Send4Bit  ( command  );      /* Gui 4 bit thap*/
LCD_Enable () ;
}
// Ham Khoi Tao LCD
void LCD_Init ( void )
{
LCD_Send4Bit(0x00);
//delay_ms(20);
_delay_cycles(20000);
P1OUT &= ~LCD_RS;
P1OUT &= ~LCD_RW;
LCD_Send4Bit(0x03);
LCD_Enable();
//delay_ms(5);
_delay_cycles(5000);
LCD_Enable();
//delay_us(100);
_delay_cycles(100);
LCD_Enable();
LCD_Send4Bit(0x02);
LCD_Enable();
LCD_SendCommand( 0x28 );         // giao thuc 4 bit, hien thi 2 hang, ki tu 5x8
LCD_SendCommand( 0x0c);          // cho phep hien thi man hinh
LCD_SendCommand( 0x06 );         // tang ID, khong dich khung hinh
LCD_Clear();                     // xoa toan bo khung hinh
}
//Ham Thiet lap vi tri con tro
void LCD_Gotoxy(uint8_t  x, uint8_t  y)
{
 uint8_t  address;
 if(!y)
 address = (0x80+x);
 else
 address = (0xC0+x);
 delay_ms(1);
 LCD_SendCommand(address);
 //delay_ms(5);
 _delay_cycles(5000);
}

// Ham Xoa Man Hinh LCD
void LCD_Clear()
{
 LCD_SendCommand(0x01);
 //delay_ms(5);
 _delay_cycles(5000);
}

// Ham Gui 1 Ki Tu Len LCD
void LCD_PutChar ( uint8_t  Data )
{
P1OUT |= LCD_RS;
LCD_SendCommand( Data );
P1OUT &= ~LCD_RS;
}

//Ham Gui Mot Chuoi Ki Tu Len LCD
void LCD_Puts (uint8_t *s)
{
  while (*s)
  {
     LCD_PutChar(*s);
     s++;
  }
}
#define DHT_ER       0
#define DHT_OK       1

/*******************************************************************************
Noi Dung    :   Doc gia tri nhiet do, do am tu DHT.
Tham Bien   :   *tem:    con tro luu tru gia tri nhiet do.
                *humi:   con tro luu tru gia tri do am.
Tra Ve      :   - DHT_OK:   Neu do nhiet do,do am thanh cong.
                - DHT_ER:   Neu do nhiet do, do am xay ra loi.
 *******************************************************************************/

uint8_t DHT_GetTemHumi (uint8_t *tem,uint8_t *humi);
uint8_t DHT_GetTemHumi (uint8_t *tem,uint8_t *humi)
{
    uint8_t buffer[5]={0,0,0,0,0};
    uint8_t ii,i,checksum;

	P2DIR |= DHT_DDR_DATA;
	P2OUT |= DHT_DATA_OUT;
	//delay_us(60);
	_delay_cycles(60);
    P2OUT &= ~DHT_DATA_OUT;
    //delay_ms(25); // it nhat 18ms
    _delay_cycles(25000);
    P2OUT |= DHT_DATA_OUT;
    P2DIR &= ~DHT_DDR_DATA;
    //delay_us(60);
    _delay_cycles(60);
    if(P2IN & DHT_DATA_IN)return DHT_ER ;
    else while(!(P2IN & DHT_DATA_IN));	//Doi DaTa len 1
    //delay_us(60);
    _delay_cycles(60);
    if(!(P2IN & DHT_DATA_IN))return DHT_ER;
    else while(P2IN & DHT_DATA_IN);	 //Doi Data ve 0
    //Bat dau doc du lieu
    for(i=0;i<5;i++)
    {
        for(ii=0;ii<8;ii++)
        {
        while(!(P2IN & DHT_DATA_IN));//Doi Data len 1
        //delay_us(50);
        _delay_cycles(50);
        if(P2IN & DHT_DATA_IN)
            {
            buffer[i]|=(1<<(7-ii));
            while(P2IN & DHT_DATA_IN);//Doi Data xuong 0
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
void Buzz_On()
{
	P2OUT |= SPEAK;	
}
void Buzz_Off()
{
	P2OUT &= ~SPEAK;	
}

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
