
#include "stm32f10x.h"
#include <stdio.h>


//#include "PORTDXUAT.h"
#define TFT_BLACK                    0x0000
#define TFT_WHITE                    0xFFFF
#define TFT_RED                      0xf800
#define TFT_GREEN                    0x07e0
#define TFT_BLUE                     0x001F
#define TFT_SILVER                   0xC618
#define TFT_GRAY                     0x8410
#define TFT_MAROON                   0x8000
#define TFT_YELLOW                   0xFFE0
#define TFT_OLIVE                    0x8400
#define TFT_AQUA                     0x07FF
#define TFT_TEAL                     0x0410
#define TFT_NAVY                     0x0010
#define TFT_FUCHSIA                  0xF81F
#define TFT_PURPLE                   0x8010
//______________________________________TFT 1.8'' SIZE ____________________________________
#define TFT_18_X_MAIN_SIZE            128
#define TFT_18_Y_MAIN_SIZE            160
#define TFT_18_X_SUB_SIZE             96
#define TFT_18_Y_SUB_SIZE             64
#define TFT_18_NUM_PIXEL_MAIN         TFT_18_X_MAIN_SIZE*TFT_18_Y_MAIN_SIZE
#define TFT_18_NUM_PIXEL_SUB          TFT_18_X_SUB_SIZE*TFT_18_Y_SUB_SIZE
#define TFT_18_START_X_SUB            0		 
#define TFT_18_START_Y_SUB            16
#define TFT_18_END_X_SUB              95		 
#define TFT_18_END_Y_SUB              79
#define TFT_18_START_X_MAIN           0
#define TFT_18_START_Y_MAIN           80
#define TFT_18_END_X_MAIN             127
#define TFT_18_END_Y_MAIN             239
#define TFT_MAIN_LCD                  0
#define TFT_SUB_LCD                   1
#define  LCD_TFT		 GPIOD
uint8_t  TFT_18_CS;		 //GPIO_Pin_8
uint8_t  TFT_18_RS;		 //GPIO_Pin_9
uint8_t  TFT_18_RW;		//GPIO_Pin_10
uint8_t  TFT_18_RD;		 //GPIO_Pin_11
uint8_t  TFT_18_RST;	    //GPIO_Pin_12
uint16_t  TFT_18_DATA;
static uint16_t Pen_Color;


uint8_t font_5x7[][5] =
                        {0x00, 0x00, 0x00, 0x00, 0x00, // SPACE
                         0x00, 0x00, 0x5F, 0x00, 0x00, // !
                         0x00, 0x03, 0x00, 0x03, 0x00, // "
                         0x14, 0x3E, 0x14, 0x3E, 0x14, // #
                         0x24, 0x2A, 0x7F, 0x2A, 0x12, // $
                         0x43, 0x33, 0x08, 0x66, 0x61, // %
                         0x36, 0x49, 0x55, 0x22, 0x50, // &
                         0x00, 0x05, 0x03, 0x00, 0x00, // '
                         0x00, 0x1C, 0x22, 0x41, 0x00, // (
                         0x00, 0x41, 0x22, 0x1C, 0x00, // )
                         0x14, 0x08, 0x3E, 0x08, 0x14, // *
                         0x08, 0x08, 0x3E, 0x08, 0x08, // +
                         0x00, 0x50, 0x30, 0x00, 0x00, // ,
                         0x08, 0x08, 0x08, 0x08, 0x08, // -
                         0x00, 0x60, 0x60, 0x00, 0x00, // .
                         0x20, 0x10, 0x08, 0x04, 0x02, // /
                         0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
                         0x00, 0x04, 0x02, 0x7F, 0x00, // 1
                         0x42, 0x61, 0x51, 0x49, 0x46, // 2
                         0x22, 0x41, 0x49, 0x49, 0x36, // 3
                         0x18, 0x14, 0x12, 0x7F, 0x10, // 4
                         0x27, 0x45, 0x45, 0x45, 0x39, // 5
                         0x3E, 0x49, 0x49, 0x49, 0x32, // 6
                         0x01, 0x01, 0x71, 0x09, 0x07, // 7
                         0x36, 0x49, 0x49, 0x49, 0x36, // 8
                         0x26, 0x49, 0x49, 0x49, 0x3E, // 9
                         0x00, 0x36, 0x36, 0x00, 0x00, // :
                         0x00, 0x56, 0x36, 0x00, 0x00, // ;
                         0x08, 0x14, 0x22, 0x41, 0x00, // <
                         0x14, 0x14, 0x14, 0x14, 0x14, // =
                         0x00, 0x41, 0x22, 0x14, 0x08, // >
                         0x02, 0x01, 0x51, 0x09, 0x06, // ?
                         0x3E, 0x41, 0x59, 0x55, 0x5E, // @
                         0x7E, 0x09, 0x09, 0x09, 0x7E, // A
                         0x7F, 0x49, 0x49, 0x49, 0x36, // B
                         0x3E, 0x41, 0x41, 0x41, 0x22, // C
                         0x7F, 0x41, 0x41, 0x41, 0x3E, // D
                         0x7F, 0x49, 0x49, 0x49, 0x41, // E
                         0x7F, 0x09, 0x09, 0x09, 0x01, // F
                         0x3E, 0x41, 0x41, 0x49, 0x3A, // G
                         0x7F, 0x08, 0x08, 0x08, 0x7F, // H
                         0x00, 0x41, 0x7F, 0x41, 0x00, // I
                         0x30, 0x40, 0x40, 0x40, 0x3F, // J
                         0x7F, 0x08, 0x14, 0x22, 0x41, // K
                         0x7F, 0x40, 0x40, 0x40, 0x40, // L
                         0x7F, 0x02, 0x0C, 0x02, 0x7F, // M
                         0x7F, 0x02, 0x04, 0x08, 0x7F, // N
                         0x3E, 0x41, 0x41, 0x41, 0x3E, // O
                         0x7F, 0x09, 0x09, 0x09, 0x06, // P
                         0x1E, 0x21, 0x21, 0x21, 0x5E, // Q
                         0x7F, 0x09, 0x09, 0x09, 0x76, // R
                         0x26, 0x49, 0x49, 0x49, 0x32, // S
                         0x01, 0x01, 0x7F, 0x01, 0x01, // T
                         0x3F, 0x40, 0x40, 0x40, 0x3F, // U
                         0x1F, 0x20, 0x40, 0x20, 0x1F, // V
                         0x7F, 0x20, 0x10, 0x20, 0x7F, // W
                         0x41, 0x22, 0x1C, 0x22, 0x41, // X
                         0x07, 0x08, 0x70, 0x08, 0x07, // Y
                         0x61, 0x51, 0x49, 0x45, 0x43, // Z
                         0x00, 0x7F, 0x41, 0x00, 0x00, // [
                         0x02, 0x04, 0x08, 0x10, 0x20, // '\'
                         0x00, 0x00, 0x41, 0x7F, 0x00, // ]
                         0x04, 0x02, 0x01, 0x02, 0x04, // ^
                         0x40, 0x40, 0x40, 0x40, 0x40, // _
                         0x00, 0x01, 0x02, 0x04, 0x00, // `
                         0x20, 0x54, 0x54, 0x54, 0x78, // a
                         0x7F, 0x44, 0x44, 0x44, 0x38, // b
                         0x38, 0x44, 0x44, 0x44, 0x44, // c
                         0x38, 0x44, 0x44, 0x44, 0x7F, // d
                         0x38, 0x54, 0x54, 0x54, 0x18, // e
                         0x04, 0x04, 0x7E, 0x05, 0x05, // f
                         0x08, 0x54, 0x54, 0x54, 0x3C, // g
                         0x7F, 0x08, 0x04, 0x04, 0x78, // h
                         0x00, 0x44, 0x7D, 0x40, 0x00, // i
                         0x20, 0x40, 0x44, 0x3D, 0x00, // j
                         0x7F, 0x10, 0x28, 0x44, 0x00, // k
                         0x00, 0x41, 0x7F, 0x40, 0x00, // l
                         0x7C, 0x04, 0x78, 0x04, 0x78, // m
                         0x7C, 0x08, 0x04, 0x04, 0x78, // n
                         0x38, 0x44, 0x44, 0x44, 0x38, // o
                         0x7C, 0x14, 0x14, 0x14, 0x08, // p
                         0x08, 0x14, 0x14, 0x14, 0x7C, // q
                         0x00, 0x7C, 0x08, 0x04, 0x04, // r
                         0x48, 0x54, 0x54, 0x54, 0x20, // s
                         0x04, 0x04, 0x3F, 0x44, 0x44, // t
                         0x3C, 0x40, 0x40, 0x20, 0x7C, // u
                         0x1C, 0x20, 0x40, 0x20, 0x1C, // v
                         0x3C, 0x40, 0x30, 0x40, 0x3C, // w
                         0x44, 0x28, 0x10, 0x28, 0x44, // x
                         0x0C, 0x50, 0x50, 0x50, 0x3C, // y
                         0x44, 0x64, 0x54, 0x4C, 0x44, // z
                         0x00, 0x08, 0x36, 0x41, 0x41, // {
                         0x00, 0x00, 0x7F, 0x00, 0x00, // |
                         0x41, 0x41, 0x36, 0x08, 0x00, // }
                         0x02, 0x01, 0x02, 0x04, 0x02};// ~  
												 
												 
								
												 
												 
												 
												 
												 


void delay_ms(__IO uint32_t num)
{
	__IO uint32_t index = 0;

	for(index = (50 * num); index != 0; index--)
	{
	}
}




//mau net ve
void TFT_18_SetPenColor(uint16_t color)
{
			Pen_Color=color;
}




/*************************************************************************************
Noi dung            :     Ghi mot lenh vao LCD TFT 1.8 Inch
Tham Bien           :     Value       :   Gia tri cua lenh.
                          Address     :   Dia chi thanh ghi.
Tra Ve              :     Khong       
Cach su dung        :     TFT_18_WriteCommand(0x44,0x1234);
*************************************************************************************/

void TFT_18_WriteCommand(uint8_t Address,uint16_t Value)
{
	TFT_18_CS = 0;
	TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	TFT_18_RS = 0;
	TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	TFT_18_DATA = 0x00;
	TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	TFT_18_RW = 0;
	TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	TFT_18_RW = 1;
	TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	TFT_18_DATA = Address;
	TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	TFT_18_RW = 0;
	TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	TFT_18_RW = 1;
		TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	TFT_18_RS = 1;
	TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	TFT_18_DATA = (uint8_t)(Value>>8);
	TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	TFT_18_RW = 0;
		TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	TFT_18_RW = 1;
		TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	TFT_18_RS = 1;
		TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	TFT_18_DATA = (uint8_t)Value;
		TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	TFT_18_RW = 0;
		TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	TFT_18_RW = 1;
		TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	TFT_18_RS = 0;
		TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	TFT_18_CS = 1;
		TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
}






/*************************************************************************************
Noi dung            :     Ham thiet lap toa do cho con tro hien thi
Tham Bien           :     X_Start      :   toa do x bat dau cua con tro
                          Y_Start      :   toa do y bat dau cua con tro.
                          X_End        :   toa do x ket thuc cua con tro
                          Y_End        :   toa do y ket thuc cua con tro.
Tra Ve              :     Khong.
Cach su dung        :     TFT_18_SetXY(0,0,10,40);
*************************************************************************************/

void TFT_18_SetXY(uint8_t X_Start,uint8_t Y_Start,uint8_t X_End,uint8_t Y_End)
{
	uint16_t temp_x,temp_y,temp;
	temp_x=X_End;
	temp_x<<=8;
	temp_x|=X_Start;
	temp_y=Y_End;
	temp_y<<=8;
	temp_y|=Y_Start;
	temp=Y_Start;
	temp<<=8;
	temp|=X_Start;
	TFT_18_WriteCommand(0x44,temp_x);
	TFT_18_WriteCommand(0x45,temp_y);
	TFT_18_WriteCommand(0x21,temp);
	TFT_18_WriteCommand(0x22,0);
}
//Noi dung            :     Ve mot duong ke ngang.


/***********************************************************************************
Noi dung            :     Ghi du lieu len LCD TFT 1.8 Inch
Tham Bien           :     Value       :  Gia tri can ghi.
Tra Ve              :     Khong
Cach su dung        :     TFT_18_WriteData(Data);
***********************************************************************************/
void TFT_18_WriteData(uint16_t Value)
{
	TFT_18_DATA = (uint8_t)(Value>>8);
		TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	TFT_18_RW = 0;
	TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	
	TFT_18_RW = 1;
		TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	TFT_18_DATA = (uint8_t)Value;
		TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	TFT_18_RW = 0;
		TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	TFT_18_RW = 1;
		TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	 GPIO_Write(LCD_TFT,TFT_18_DATA);
}











void TFT_18_DrawHLine(uint8_t x, uint8_t y, uint8_t l)
{
	uint8_t i;

		y=y+TFT_18_START_Y_MAIN;
		TFT_18_SetXY(x,y,x+l,y);
	TFT_18_CS = 0;
		TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	TFT_18_RS = 1;
		TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	for (i=0; i<l+1;i++)
	{
			TFT_18_WriteData(Pen_Color);
	}
	TFT_18_CS = 1;
		TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
}
//Noi dung            :     Ve mot duong ke doc.

void TFT_18_DrawVLine(uint8_t x, uint8_t y, uint8_t l)
{
	uint8_t i;
		y=y+TFT_18_START_Y_MAIN;
		TFT_18_SetXY(x,y,x,y+l);
	  TFT_18_CS = 0;
	TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);	
	TFT_18_RS = 1;
		TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
		for (i=0; i<l+1; i++)
		{
			TFT_18_WriteData(Pen_Color);
		}
	 TFT_18_CS = 1;
	 TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	 GPIO_Write(LCD_TFT,TFT_18_DATA);
}
/*************************************************************************************
Noi dung            :     Ve mot duong chu nhat .
Tham Bien           :     x1          :   Toa do x1 cua duong chu nhat.
                          y1          :   Toa do y1 cua duong chu nhat.
                          x2          :   Toa do x2 cua duong chu nhat.
                          y2          :   Toa do y2 cua duong chu nhat.
Tra Ve              :     Khong
Cach su dung        :     TFT_18_DrawRect(10, 30, 100,110);
*************************************************************************************/

void TFT_18_DrawRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
	uint8_t dx,dy;
	if (x1>x2)
	{
		dx=x1;
		x1=x2;
		x2=dx;
	}
	if (y1>y2)
	{
		dy=y1;
		y1=y2;
		y2=dy;
	}
	TFT_18_DrawHLine(x1, y1, x2-x1);
	TFT_18_DrawHLine(x1, y2, x2-x1);
	TFT_18_DrawVLine(x1, y1, y2-y1);
	TFT_18_DrawVLine(x2, y1, y2-y1);
}
/*************************************************************************************
Noi dung            :     Ve mot hinh chu nhat .
Tham Bien           :     x1          :   Toa do x1 cua hinh chu nhat.
                          y1          :   Toa do y1 cua hinh chu nhat.
                          x2          :   Toa do x2 cua hinh chu nhat.
                          y2          :   Toa do y2 cua hinh chu nhat.
Tra Ve              :     Khong
Cach su dung        :     TFT_18_FillRect(10, 30, 100,110);
*************************************************************************************/

void TFT_18_FillRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
	uint8_t dx,dy,i;
	if (x1>x2)
	{
		dx=x1;
		x1=x2;
		x2=dx;
	}
	if (y1>y2)
	{
		dy=y1;
		y1=y2;
		y2=dy;
	}

	for (i=0; i<((x2-x1)/2)+1; i++)
	{
		TFT_18_DrawVLine(x1+i, y1, y2-y1);
		TFT_18_DrawVLine(x2-i, y1, y2-y1);
	}
}

/*************************************************************************************
Noi dung            :     Khoi tao man hinh LCD TFT
Tham Bien           :     Khong.
Tra Ve              :     Khong
Cach su dung        :     TFT_18_Init();
*************************************************************************************/

void TFT_18_Init(void)

{
	
  TFT_18_CS=1;
		TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	TFT_18_RS=1;
		TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	TFT_18_RW=1;
		TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	TFT_18_RD=1;
		TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	TFT_18_RST=1;
		TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
  TFT_18_DATA=0xff;
		TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
  TFT_18_RST = 0;
		TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	delay_ms(200);
	TFT_18_RST = 1;
		TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	delay_ms(200);
  TFT_18_WriteCommand(0x00,0x0001);		
  delay_ms(10);
  TFT_18_WriteCommand(0x03,0x0030);
  TFT_18_WriteCommand(0x01,0x011D);
  delay_ms(100);
  TFT_18_WriteCommand(0x0a,0x0106); 
  delay_ms(10);

  TFT_18_WriteCommand(0x08,0x0707);
  TFT_18_WriteCommand(0x0c,0x01);
  TFT_18_WriteCommand(0x02,0x0400);
  delay_ms(1);
  TFT_18_WriteCommand(0x0a,0x0107); 
  delay_ms(1);

  TFT_18_WriteCommand(0x12,0x0001);
  delay_ms(1);
  TFT_18_WriteCommand(0x0a,0x0101); 
  delay_ms(1);
  
  TFT_18_WriteCommand(0x11,0x0505);
  TFT_18_WriteCommand(0x14,0x2c0f); 
  delay_ms(1);
  TFT_18_WriteCommand(0x0a,0x0102); 
  delay_ms(1);
  TFT_18_WriteCommand(0x10,0x1a10);
  delay_ms(1);
  TFT_18_WriteCommand(0x0a,0x0100); 
  delay_ms(1);

  TFT_18_WriteCommand(0x13,0x0616);
  delay_ms(1);
  TFT_18_WriteCommand(0x0a,0x0101); 
  delay_ms(1);

  TFT_18_WriteCommand(0x30,0x0003);
  TFT_18_WriteCommand(0x31,0x0404);
  TFT_18_WriteCommand(0x32,0x0303);
  TFT_18_WriteCommand(0x33,0x0406);
  TFT_18_WriteCommand(0x34,0x0404);
  TFT_18_WriteCommand(0x35,0x0303);
  TFT_18_WriteCommand(0x36,0x0407);
  TFT_18_WriteCommand(0x37,0x0604);
  TFT_18_WriteCommand(0x07,0x0037);
  delay_ms(1);
  TFT_18_WriteCommand(0x0a,0x0100);
  delay_ms(1); 
    
  TFT_18_WriteCommand(0x10,0x1a10);
  delay_ms(1);
  TFT_18_WriteCommand(0x0a,0x0100); 
  delay_ms(1);	
	TFT_18_WriteCommand(0x13,0x0616);
    
  delay_ms(1);
  TFT_18_WriteCommand(0x0a,0x0101); 
  delay_ms(1);
  
  TFT_18_WriteCommand(0x07,0x0037);
  delay_ms(1);
  TFT_18_WriteCommand(0x0a,0x0100); 
  delay_ms(1);   
}
/*************************************************************************************
Noi dung            :     Dien day man hinh chinh mot mau.
Tham Bien           :     color       :   Gia tri cua mau
Tra Ve              :     Khong
Cach su dung        :     TFT_18_ClearMain(TFT_WHITE);
*************************************************************************************/

void TFT_18_ClearMain(uint16_t color)
{
	uint16_t num;
	TFT_18_SetXY(TFT_18_START_X_MAIN,TFT_18_START_Y_MAIN,TFT_18_END_X_MAIN,TFT_18_END_Y_MAIN);
	  TFT_18_CS = 0;
			TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	 TFT_18_RS = 1;
			TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	for(num=TFT_18_NUM_PIXEL_MAIN;num>0;num--)
	{
		TFT_18_WriteData(color);
	}
	TFT_18_CS = 1;
			TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
}
/*************************************************************************************
Noi dung            :     Dien day man hinh phu mot mau.
Tham Bien           :     color       :   Gia tri cua mau
Tra Ve              :     Khong
Cach su dung        :     TFT_18_ClearSub(TFT_WHITE);
*************************************************************************************/

void TFT_18_ClearSub(uint16_t color)
{
	uint16_t num;
	TFT_18_SetXY(TFT_18_START_X_SUB,TFT_18_START_Y_SUB,TFT_18_END_X_SUB,TFT_18_END_Y_SUB);
  TFT_18_CS = 0;
		TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);	
	TFT_18_RS = 1;
			TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	for(num=TFT_18_NUM_PIXEL_SUB;num>0;num--)
	{
		TFT_18_WriteData(color);
	}
	 TFT_18_CS = 1;
			TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
}
/*************************************************************************************
Noi dung            :     Ham ve mot diem anh.
Tham Bien           :     color   :   gia tri mau cua diem anh.
Tra Ve              :     khong
Cach su dung        :     TFT_18_DrawPixel(TFT_RED);
*************************************************************************************/
void TFT_18_DrawPixel(uint8_t x,uint8_t y)
{
	TFT_18_SetXY(x,y+TFT_18_START_Y_MAIN,x,y+TFT_18_START_Y_MAIN);
	 TFT_18_CS=0;
		TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);	
	TFT_18_RS = 1;
			TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	TFT_18_WriteData(Pen_Color);
	 TFT_18_CS=1;
			TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
}
/*************************************************************************************
Noi dung            :     Ham gui mot ki tu len man hinh TFT.
Tham Bien           :     c       :   ki tu can hien thi
                          x       :   toa do ngang cua ki tu.
                          y       :   toa do y cua ki tu.
                          size_   :   kich thuoc chu.
Tra Ve              :     Khong.
Cach su dung        :     TFT_18_PutChar('N',0,240,1);
*************************************************************************************/

void TFT_18_PutChar(uint8_t c,uint8_t x,uint8_t y,uint8_t size_)
{
	uint8_t i,j,k,l,temp_c;
	c-=32;
	for(j=0;j<5;j++)
			{
				temp_c=font_5x7[c][j];
				for(i=0;i<8;i++)
				{   
					if((temp_c&(1<<i))!=0) 
					{
						for(k=0;k<size_;k++)
						{
							for(l=0;l<size_;l++)
							TFT_18_DrawPixel(x+j*size_+k,y+i*size_+l);
						}
					} 
				}
			}
}
/*************************************************************************************
Noi dung            :     Gui mot chuoi ki tu len man hinh TFT.
Tham Bien           :     x           :   Toa do x cua chuoi ki tu.
                          y           :   Toa do y cua chuoi ki tu.
                          size_       :   Kich thuoc chu.
Tra Ve              :     Khong
Cach su dung        :     TFT_18_PutString("MinhHaGroup",10,30,1);
*************************************************************************************/
void TFT_18_PutString(uint8_t *s,uint8_t x,uint8_t y,uint8_t size_)
{
	while (*s) 
	{ 
		TFT_18_PutChar(*s,x,y,size_);
		x=x+size_*6;
		if(x>=TFT_18_END_X_MAIN-size_*5)
		{
				y=y+size_*8;
				x=0;
		}
		s++;
    }
}
/*************************************************************************************
Noi dung            :     Ham ve mot hinh anh len man hinh LCD TFT.
Tham Bien           :     x       :   toa do nang cua hinh anh
                          y       :   toa do y cua hinh anh
                          size_x  :   kich thuoc hinh anh theo phuong ngang.
                          size_y  :   kich thuoc hinh anh theo phuong doc.
                          Bitmap  :   con tro luu tru ma cua hinh anh.
Tra Ve              :     Khong.
Cach su dung        :     TFT_DrawBitMap(0,0,20,30,&LOGO_MH);
*************************************************************************************/

void TFT_18_DrawBitMap(uint8_t x, uint8_t y, uint8_t size_x, uint8_t size_y, uint16_t  *Bitmap)//PRO_DATA
{
	uint16_t temp;
	uint16_t  i,j;
	TFT_18_SetXY(x,TFT_18_START_Y_MAIN+y,x+size_x-1,TFT_18_START_Y_MAIN+y+size_y-1);
	TFT_18_CS = 0;
		TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);	
	TFT_18_RS = 1;
			TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
				for(i=0;i<size_y;i++)
				{
          for(j=0;j<size_x;j++)
					{
					temp=Bitmap[i*size_x+j];
					TFT_18_WriteData(temp);
					}
				}
	TFT_18_CS = 1;
						TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
}
void TFT_18_PutCharDelay(uint8_t casc,uint8_t postion_x,uint8_t postion_y,uint8_t size_,uint16_t time)
{
	uint8_t i,j,k,l,temp_c;
	casc-=32;
	for(j=0;j<5;j++)
			{
				temp_c=font_5x7[casc][j];
				for(i=0;i<8;i++)
				{   
					if((temp_c&(1<<i))!=0) 
					{
						for(k=0;k<size_;k++)
						{
							for(l=0;l<size_;l++)
							{
							TFT_18_DrawPixel(postion_x+j*size_+k,postion_y+i*size_+l);
							delay_ms(time);
							}
						}
					} 
				}
			}
}
void TFT_18_PutStringDelay1(uint8_t *s,uint8_t x,uint8_t y, uint8_t size_,uint16_t time)
{
	while (*s) 
	{ 
		TFT_18_PutChar(*s,x,y,size_);
		x=x+size_*6;
		if(x>=TFT_18_END_X_MAIN-size_*5)
		{
				y=y+size_*8;
				x=0;
		}
		s++;
		delay_ms(time);
    }
}
void TFT_18_PutStringDelay2(uint8_t *s,uint8_t x,uint8_t y, uint8_t size_,uint16_t time)
{
	while (*s) 
	{ 
		TFT_18_PutCharDelay(*s,x,y,size_,time);
		x=x+size_*6;
		if(x>=TFT_18_END_X_MAIN-size_*5)
		{
				y=y+size_*8;
				x=0;
		}
		s++;
    }
}
void TFT_18_DrawLogo(uint16_t *Logo) //PRO_DATA
{
    uint16_t temp; 
    uint16_t i,j;
    TFT_18_SetXY(TFT_18_START_X_SUB,TFT_18_START_Y_SUB,TFT_18_END_X_SUB,TFT_18_END_Y_SUB);
	  TFT_18_CS = 0;
			TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	
	    TFT_18_RS = 1;
			TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
    	GPIO_Write(LCD_TFT,TFT_18_DATA);
				for(i=0;i<TFT_18_Y_SUB_SIZE;i++)
				{
                    for(j=TFT_18_X_SUB_SIZE;j>0;j--)
					{
                    temp=Logo[TFT_18_NUM_PIXEL_SUB-i*TFT_18_X_SUB_SIZE+j-1];
					TFT_18_WriteData(temp);
					}
				}
	     TFT_18_CS = 1;       
			 TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	     GPIO_Write(LCD_TFT,TFT_18_DATA);
}
void TFT_18_TEST(void)
{
	uint16_t temp,num;
	uint16_t color[]={0xf800,0x07e0,0x001f,0xffe0,0x0000,0xffff,0x07ff,0xf81f};
	uint8_t n;
	TFT_18_SetXY(0,80,127,239);
	 TFT_18_CS = 0;
	 	TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
   TFT_18_RS = 1;
		TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	for(n=0;n<8;n++)
	{
	    temp=color[n];
			for(num=20*128;num>0;num--)
		  TFT_18_WriteData(temp);
	}
	  TFT_18_CS = 1;
			TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	delay_ms(5000);
	delay_ms(5000);
	for(n=0;n<8;n++)
	{
		TFT_18_SetXY(0,80,127,239);
		TFT_18_CS = 0;
			TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);	
		TFT_18_RS = 1;
				TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
	  temp=color[n];
		for(num=160*128;num>0;num--)
		{
			TFT_18_WriteData(temp);
		}
		delay_ms(5000);
	}
	  TFT_18_CS = 1;
			TFT_18_DATA=((TFT_18_CS+TFT_18_RS*2+TFT_18_RW*4+TFT_18_RD*8+TFT_18_RST*16)*0x0100)+(TFT_18_DATA&0xe0ff);
	GPIO_Write(LCD_TFT,TFT_18_DATA);
}


