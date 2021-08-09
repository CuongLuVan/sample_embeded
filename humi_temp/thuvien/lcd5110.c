



/**
  ******************************************************************************
  * Ten Tep      :        nokia5110.c
  * Tac Gia      :        Nguyen Quy Nhat
  * Cong Ty      :        MinhHaGroup
  * Website      :        BanLinhKien.Vn
  * Phien Ban    :        V1.0.0
  * Ngay         :        31-07-2012
  * Tom Tat      :        Dinh nghia cac ham dieu khien LCD Nokia5110.
  *           
  *
  ******************************************************************************
  * Chu Y        :   Phai dinh nghia cac chan su dung cho LCD nokia5110 vao file main.h
  *                     Vi Du:
#define NOKIA5110_RST               PORTC_1
#define NOKIA5110_SCE               PORTC_2
#define NOKIA5110_DC                PORTC_3
#define NOKIA5110_DATA              PORTC_4
#define NOKIA5110_CLK               PORTC_5

#define DDR_NOKIA5110_SCE           DDRC_1
#define DDR_NOKIA5110_RST           DDRC_2
#define DDR_NOKIA5110_DC            DDRC_3
#define DDR_NOKIA5110_DATA          DDRC_4
#define DDR_NOKIA5110_CLK           DDRC_5                          
  ******************************************************************************
**/
/*********************************** VI DU ************************************
    uint8_t str[16],humi;
    NOKIA5110_Init();
    sprintf(str,"BanLinhKien.Vn");
    NOKIA5110_Puts(str);
    ......
    sprintf(str,"Do Am: %u",humi);
    NOKIA5110_Gotoxy(0,1);
    NOKIA5110_Puts(str);
    NOKIA5110_PutChar('%');
*******************************************************************************/
#include "lcd5110.h"
#include <string.h>
 //extern PRO_DATA uint8_t  font6x8[92][6];
 /*******************************************************************************
Noi Dung    :   Gui 1 Byte du lieu den Nokia5110
Tham Bien   :   Data     :   Byte du lieu.
Tra Ve      :   Khong.
********************************************************************************/

#define FONT_X_SIZE      6
#define FONT_Y_SIZE      8
 uint8_t  font6x8[92][6] =
{
 0x00, 0x00, 0x00, 0x00, 0x00,// sp
 0x00, 0x00, 0x00, 0x2f, 0x00, 0x00,// !
 0x00, 0x00, 0x07, 0x00, 0x07, 0x00,// "
 0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14,// #
 0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12,// $
 0x00, 0x62, 0x64, 0x08, 0x13, 0x23,// %
 0x00, 0x36, 0x49, 0x55, 0x22, 0x50,// &
 0x00, 0x00, 0x05, 0x03, 0x00, 0x00,// '
 0x00, 0x00, 0x1c, 0x22, 0x41, 0x00,// (
 0x00, 0x00, 0x41, 0x22, 0x1c, 0x00,// )
 0x00, 0x14, 0x08, 0x3E, 0x08, 0x14,// *
 0x00, 0x08, 0x08, 0x3E, 0x08, 0x08,// +
 0x00, 0x00, 0x00, 0xA0, 0x60, 0x00,// ,
 0x00, 0x08, 0x08, 0x08, 0x08, 0x08,// -
 0x00, 0x00, 0x60, 0x60, 0x00, 0x00,// .
 0x00, 0x20, 0x10, 0x08, 0x04, 0x02,// /
 0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E,// 0
 0x00, 0x00, 0x42, 0x7F, 0x40, 0x00,// 1
 0x00, 0x42, 0x61, 0x51, 0x49, 0x46,// 2
 0x00, 0x21, 0x41, 0x45, 0x4B, 0x31,// 3
 0x00, 0x18, 0x14, 0x12, 0x7F, 0x10,// 4
 0x00, 0x27, 0x45, 0x45, 0x45, 0x39,// 5
 0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30,// 6
 0x00, 0x01, 0x71, 0x09, 0x05, 0x03,// 7
 0x00, 0x36, 0x49, 0x49, 0x49, 0x36,// 8
 0x00, 0x06, 0x49, 0x49, 0x29, 0x1E,// 9
 0x00, 0x00, 0x36, 0x36, 0x00, 0x00,// :
 0x00, 0x00, 0x56, 0x36, 0x00, 0x00,// ;
 0x00, 0x08, 0x14, 0x22, 0x41, 0x00,// <
 0x00, 0x14, 0x14, 0x14, 0x14, 0x14,// =
 0x00, 0x00, 0x41, 0x22, 0x14, 0x08,// >
 0x00, 0x02, 0x01, 0x51, 0x09, 0x06,// ?
 0x00, 0x32, 0x49, 0x59, 0x51, 0x3E,// @
 0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C,// A
 0x00, 0x7F, 0x49, 0x49, 0x49, 0x36,// B
 0x00, 0x3E, 0x41, 0x41, 0x41, 0x22,// C
 0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C,// D
 0x00, 0x7F, 0x49, 0x49, 0x49, 0x41,// E
 0x00, 0x7F, 0x09, 0x09, 0x09, 0x01,// F
 0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A,// G
 0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F,// H
 0x00, 0x00, 0x41, 0x7F, 0x41, 0x00,// I
 0x00, 0x20, 0x40, 0x41, 0x3F, 0x01,// J
 0x00, 0x7F, 0x08, 0x14, 0x22, 0x41,// K
 0x00, 0x7F, 0x40, 0x40, 0x40, 0x40,// L
 0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F,// M
 0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F,// N
 0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E,// O
 0x00, 0x7F, 0x09, 0x09, 0x09, 0x06,// P
 0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E,// Q
 0x00, 0x7F, 0x09, 0x19, 0x29, 0x46,// R
 0x00, 0x46, 0x49, 0x49, 0x49, 0x31,// S
 0x00, 0x01, 0x01, 0x7F, 0x01, 0x01,// T
 0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F,// U
 0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F,// V
 0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F,// W
 0x00, 0x63, 0x14, 0x08, 0x14, 0x63,// X
 0x00, 0x07, 0x08, 0x70, 0x08, 0x07,// Y
 0x00, 0x61, 0x51, 0x49, 0x45, 0x43,// Z
 0x00, 0x00, 0x7F, 0x41, 0x41, 0x00,// [
 0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55,// 55
 0x00, 0x00, 0x41, 0x41, 0x7F, 0x00,// ]
 0x00, 0x04, 0x02, 0x01, 0x02, 0x04,// ^
 0x00, 0x40, 0x40, 0x40, 0x40, 0x40,// _
 0x00, 0x00, 0x01, 0x02, 0x04, 0x00,// '
 0x00, 0x20, 0x54, 0x54, 0x54, 0x78,// a
 0x00, 0x7F, 0x48, 0x44, 0x44, 0x38,// b
 0x00, 0x38, 0x44, 0x44, 0x44, 0x20,// c
 0x00, 0x38, 0x44, 0x44, 0x48, 0x7F,// d
 0x00, 0x38, 0x54, 0x54, 0x54, 0x18,// e
 0x00, 0x08, 0x7E, 0x09, 0x01, 0x02,// f
 0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C,// g
 0x00, 0x7F, 0x08, 0x04, 0x04, 0x78,// h
 0x00, 0x00, 0x44, 0x7D, 0x40, 0x00,// i
 0x00, 0x40, 0x80, 0x84, 0x7D, 0x00,// j
 0x00, 0x7F, 0x10, 0x28, 0x44, 0x00,// k
 0x00, 0x00, 0x41, 0x7F, 0x40, 0x00,// l
 0x00, 0x7C, 0x04, 0x18, 0x04, 0x78,// m
 0x00, 0x7C, 0x08, 0x04, 0x04, 0x78,// n
 0x00, 0x38, 0x44, 0x44, 0x44, 0x38,// o
 0x00, 0xFC, 0x24, 0x24, 0x24, 0x18,// p
 0x00, 0x18, 0x24, 0x24, 0x18, 0xFC,// q
 0x00, 0x7C, 0x08, 0x04, 0x04, 0x08,// r
 0x00, 0x48, 0x54, 0x54, 0x54, 0x20,// s
 0x00, 0x04, 0x3F, 0x44, 0x40, 0x20,// t
 0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C,// u
 0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C,// v
 0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C,// w
 0x00, 0x44, 0x28, 0x10, 0x28, 0x44,// x
 0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C,// y
 0x00, 0x44, 0x64, 0x54, 0x4C, 0x44,// z
 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,0x00// horiz lines
};

#define CLK_5110 GPIO_Pin_12    //PB
#define DC_5110 GPIO_Pin_1     //pb
#define CE_5110 GPIO_Pin_0    //pc
#define RST_5110 GPIO_Pin_7    //pc
#define DIN_5110 GPIO_Pin_2   //pb

#define CLK_GPIO GPIOB    //PB
#define DC_GPIO GPIOB     //pb
#define CE_GPIO GPIOB    //pc
#define RST_GPIO GPIOA    //pc
#define DIN_GPIO GPIOB   //pb


#define CLK_RCC RCC_APB2Periph_GPIOB    //PB
#define DC_RCC RCC_APB2Periph_GPIOB     //pb
#define CE_RCC RCC_APB2Periph_GPIOB    //pc
#define RST_RCC RCC_APB2Periph_GPIOA    //pc
#define DIN_RCC RCC_APB2Periph_GPIOB   //pb


void delay_ms(uint32_t dem){
	uint32_t k;
while(dem--)
  for(k=100;k!=0;k--);

}

void setup_Nokia(void){
	GPIO_InitTypeDef kieu;
	RCC_APB2PeriphClockCmd(CLK_RCC| DC_RCC | CE_RCC |RST_RCC|DIN_RCC, ENABLE);
	
	  kieu.GPIO_Pin=CLK_5110;
	  kieu.GPIO_Speed=GPIO_Speed_50MHz;
	  kieu.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIO_Init(CLK_GPIO,&kieu);

		kieu.GPIO_Pin=DC_5110;
	  kieu.GPIO_Speed=GPIO_Speed_50MHz;
	  kieu.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIO_Init(DC_GPIO,&kieu);
	
		  kieu.GPIO_Pin=CE_5110;
	  kieu.GPIO_Speed=GPIO_Speed_50MHz;
	  kieu.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIO_Init(CE_GPIO,&kieu);
	
		  kieu.GPIO_Pin=RST_5110;
	  kieu.GPIO_Speed=GPIO_Speed_50MHz;
	  kieu.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIO_Init(RST_GPIO,&kieu);
		
			  kieu.GPIO_Pin=DIN_5110;
	  kieu.GPIO_Speed=GPIO_Speed_50MHz;
	  kieu.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIO_Init(DIN_GPIO,&kieu);
}


void NOKIA5110_WriteData(uint8_t Data)
{
	uint8_t i;
	//NOKIA5110_DC=1;
	GPIO_SetBits(DC_GPIO,DC_5110);
	for(i=0;i<8;i++)
   {
      if(Data&(0x80>>i))
				GPIO_SetBits(DIN_GPIO,DIN_5110);
      else
				GPIO_ResetBits(DIN_GPIO,DIN_5110);
			GPIO_SetBits(DIN_GPIO,CLK_5110);
			delay_ms(1);
			GPIO_ResetBits(DIN_GPIO,CLK_5110);
			delay_ms(1);
      //NOKIA5110_CLK=1;
      //NOKIA5110_CLK=0;
   }
}
 /*******************************************************************************
Noi Dung    :   Gui 1 Byte du lieu den Nokia5110
Tham Bien   :   Command    :   Byte lenh.
Tra Ve      :   Khong.
********************************************************************************/
void NOKIA5110_WriteCommand(uint8_t Command)
{
   uint8_t i;
   //NOKIA5110_DC=0;
	GPIO_ResetBits(DC_GPIO,DC_5110);  
	for(i=0;i<8;i++)
   {
      if(Command&(0x80>>i)) 
				GPIO_SetBits(DIN_GPIO,DIN_5110);
      else
				GPIO_ResetBits(DIN_GPIO,DIN_5110);
			GPIO_SetBits(CLK_GPIO,CLK_5110);
			delay_ms(1);
			GPIO_ResetBits(CLK_GPIO,CLK_5110);
			delay_ms(1);
   }
}
 /*******************************************************************************
Noi Dung    :   Khoi tao LCD NOKIA 5110.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
********************************************************************************/
void NOKIA5110_Init(void)
{
   setup_nokia();
	//NOKIA5110_CLK=0;
	 GPIO_ResetBits(CLK_GPIO,CLK_5110);
	 delay_ms(20);
   //NOKIA5110_RST=0; 
	 GPIO_ResetBits(RST_GPIO,RST_5110);
   delay_ms(20);
   //NOKIA5110_RST=1;
   GPIO_SetBits(RST_GPIO,RST_5110); 
	 delay_ms(20);
   //NOKIA5110_SCE=0;
   GPIO_ResetBits(CE_GPIO,CE_5110); 
	 //NOKIA5110_WriteCommand(NIKIA5110_FUNCTION_VERTICAL_BA);
   //NOKIA5110_WriteCommand(0xCA);// Cai dat gia tri VP6 - VP0: 0b11001010
   //NOKIA5110_WriteCommand(NIKIA5110_FUNCTION_HORIZONTA_BA);
   //NOKIA5110_WriteCommand(NIKIA5110_DISPLAY_NORMAL);  
   NOKIA5110_WriteCommand(NIKIA5110_FUNCTION_HORIZONTA_EX); //0x21 Lenh them, va dung che do ngang 
   NOKIA5110_WriteCommand(0xca);
   NOKIA5110_WriteCommand(NIKIA5110_FUNCTION_HORIZONTA_BA);//0x20Lenh co ban, va dung che do ngang
   NOKIA5110_WriteCommand(NIKIA5110_DISPLAY_NORMAL);
}
 /*******************************************************************************
Noi Dung    :   Thiet lap vi tri con tro LCD NOKIA 5110.
Tham Bien   :   x: vi tri cot cua con tro. x = 0 - 83.
                y: vi tri hang cua con tro. y= 0-5.
Tra Ve      :   Khong.
********************************************************************************/
void NOKIA5110_GotoXY(uint8_t X, uint8_t Y)
{
   //NOKIA5110_SCE=0;
	 GPIO_ResetBits(CE_GPIO,CE_5110); 
	 NOKIA5110_WriteCommand(0x40 | Y);    // column
   NOKIA5110_WriteCommand(0x80 | X);    // row
}
 /*******************************************************************************
Noi Dung    :   Xoa noi dung hien thi tren LCD Nokia 5110.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
********************************************************************************/
void NOKIA5110_Clear(void)
{
   uint8_t t;
   uint8_t k;
   NOKIA5110_GotoXY(0,0); 
   //NOKIA5110_SCE=0;
	 GPIO_ResetBits(CE_GPIO,CE_5110);
   for(t=0;t<NOKIA5110_Y_ARRAY_SIZE;t++)
   {
      for(k=0;k<NOKIA5110_X_SIZE;k++)
      {
         NOKIA5110_WriteData(0x00);
      }
   }
}
 /*******************************************************************************
Noi Dung    :   Viet 1 ki tu len LCD Nokia 5110.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
********************************************************************************/
void NOKIA5110_PutChar(uint8_t C)
{
   uint8_t b;
   uint8_t line;
   b=C-32;   
   for (line=0; line<6; line++)
    NOKIA5110_WriteData(font6x8[b][line]);

}
 /*******************************************************************************
Noi Dung    :   Viet 1 chuoi ki tu len LCD Nokia 5110.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
********************************************************************************/
void NOKIA5110_Puts(uint8_t *s)
{
   while (*s)
   {
      NOKIA5110_PutChar(*s);
      s++;
   }
}


/******************************KET THUC FILE******************************
______________________________NGUYEN QUY NHAT______________________________*/

