
#include <stm32f4xx.h>
#include "lcd_320x240.h"
#include <math.h>
#include <string.h>
//#include "font.h"
//#include "anh.h"
//#include "Logo.h"
#define cbi(port, bit) GPIO_ResetBits(port,bit) // (port)&= ~(0x01<<bit)  
#define sbi(port, bit) GPIO_SetBits(port,bit) // (port) |= (0x01<<bit)
char SmallFont[][12]={         
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // <Space>
0x00,0x00,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x20,0x00,0x00, // !
0x00,0x28,0x50,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // "
0x00,0x00,0x28,0x28,0xFC,0x28,0x50,0xFC,0x50,0x50,0x00,0x00, // #
0x00,0x20,0x78,0xA8,0xA0,0x60,0x30,0x28,0xA8,0xF0,0x20,0x00, // $
0x00,0x00,0x48,0xA8,0xB0,0x50,0x28,0x34,0x54,0x48,0x00,0x00, // %
0x00,0x00,0x20,0x50,0x50,0x78,0xA8,0xA8,0x90,0x6C,0x00,0x00, // &
0x00,0x40,0x40,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // '
0x00,0x04,0x08,0x10,0x10,0x10,0x10,0x10,0x10,0x08,0x04,0x00, // (
0x00,0x40,0x20,0x10,0x10,0x10,0x10,0x10,0x10,0x20,0x40,0x00, // )
0x00,0x00,0x00,0x20,0xA8,0x70,0x70,0xA8,0x20,0x00,0x00,0x00, // *
0x00,0x00,0x20,0x20,0x20,0xF8,0x20,0x20,0x20,0x00,0x00,0x00, // +
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x40,0x80, // ,
0x00,0x00,0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x00, // -
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00, // .
0x00,0x08,0x10,0x10,0x10,0x20,0x20,0x40,0x40,0x40,0x80,0x00, // /
0x00,0x00,0x70,0x88,0x88,0x88,0x88,0x88,0x88,0x70,0x00,0x00, // 0
0x00,0x00,0x20,0x60,0x20,0x20,0x20,0x20,0x20,0x70,0x00,0x00, // 1
0x00,0x00,0x70,0x88,0x88,0x10,0x20,0x40,0x80,0xF8,0x00,0x00, // 2
0x00,0x00,0x70,0x88,0x08,0x30,0x08,0x08,0x88,0x70,0x00,0x00, // 3
0x00,0x00,0x10,0x30,0x50,0x50,0x90,0x78,0x10,0x18,0x00,0x00, // 4
0x00,0x00,0xF8,0x80,0x80,0xF0,0x08,0x08,0x88,0x70,0x00,0x00, // 5
0x00,0x00,0x70,0x90,0x80,0xF0,0x88,0x88,0x88,0x70,0x00,0x00, // 6
0x00,0x00,0xF8,0x90,0x10,0x20,0x20,0x20,0x20,0x20,0x00,0x00, // 7
0x00,0x00,0x70,0x88,0x88,0x70,0x88,0x88,0x88,0x70,0x00,0x00, // 8
0x00,0x00,0x70,0x88,0x88,0x88,0x78,0x08,0x48,0x70,0x00,0x00, // 9
0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x20,0x00,0x00, // :
0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x20,0x00, // ;
0x00,0x04,0x08,0x10,0x20,0x40,0x20,0x10,0x08,0x04,0x00,0x00, // <
0x00,0x00,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0x00,0x00, // =
0x00,0x40,0x20,0x10,0x08,0x04,0x08,0x10,0x20,0x40,0x00,0x00, // >
0x00,0x00,0x70,0x88,0x88,0x10,0x20,0x20,0x00,0x20,0x00,0x00, // ?
0x00,0x00,0x70,0x88,0x98,0xA8,0xA8,0xB8,0x80,0x78,0x00,0x00, // @
0x00,0x00,0x20,0x20,0x30,0x50,0x50,0x78,0x48,0xCC,0x00,0x00, // A
0x00,0x00,0xF0,0x48,0x48,0x70,0x48,0x48,0x48,0xF0,0x00,0x00, // B
0x00,0x00,0x78,0x88,0x80,0x80,0x80,0x80,0x88,0x70,0x00,0x00, // C
0x00,0x00,0xF0,0x48,0x48,0x48,0x48,0x48,0x48,0xF0,0x00,0x00, // D
0x00,0x00,0xF8,0x48,0x50,0x70,0x50,0x40,0x48,0xF8,0x00,0x00, // E
0x00,0x00,0xF8,0x48,0x50,0x70,0x50,0x40,0x40,0xE0,0x00,0x00, // F
0x00,0x00,0x38,0x48,0x80,0x80,0x9C,0x88,0x48,0x30,0x00,0x00, // G
0x00,0x00,0xCC,0x48,0x48,0x78,0x48,0x48,0x48,0xCC,0x00,0x00, // H
0x00,0x00,0xF8,0x20,0x20,0x20,0x20,0x20,0x20,0xF8,0x00,0x00, // I
0x00,0x00,0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x90,0xE0,0x00, // J
0x00,0x00,0xEC,0x48,0x50,0x60,0x50,0x50,0x48,0xEC,0x00,0x00, // K
0x00,0x00,0xE0,0x40,0x40,0x40,0x40,0x40,0x44,0xFC,0x00,0x00, // L
0x00,0x00,0xD8,0xD8,0xD8,0xD8,0xA8,0xA8,0xA8,0xA8,0x00,0x00, // M
0x00,0x00,0xDC,0x48,0x68,0x68,0x58,0x58,0x48,0xE8,0x00,0x00, // N
0x00,0x00,0x70,0x88,0x88,0x88,0x88,0x88,0x88,0x70,0x00,0x00, // O
0x00,0x00,0xF0,0x48,0x48,0x70,0x40,0x40,0x40,0xE0,0x00,0x00, // P
0x00,0x00,0x70,0x88,0x88,0x88,0x88,0xE8,0x98,0x70,0x18,0x00, // Q
0x00,0x00,0xF0,0x48,0x48,0x70,0x50,0x48,0x48,0xEC,0x00,0x00, // R
0x00,0x00,0x78,0x88,0x80,0x60,0x10,0x08,0x88,0xF0,0x00,0x00, // S
0x00,0x00,0xF8,0xA8,0x20,0x20,0x20,0x20,0x20,0x70,0x00,0x00, // T
0x00,0x00,0xCC,0x48,0x48,0x48,0x48,0x48,0x48,0x30,0x00,0x00, // U
0x00,0x00,0xCC,0x48,0x48,0x50,0x50,0x30,0x20,0x20,0x00,0x00, // V
0x00,0x00,0xA8,0xA8,0xA8,0x70,0x50,0x50,0x50,0x50,0x00,0x00, // W
0x00,0x00,0xD8,0x50,0x50,0x20,0x20,0x50,0x50,0xD8,0x00,0x00, // X
0x00,0x00,0xD8,0x50,0x50,0x20,0x20,0x20,0x20,0x70,0x00,0x00, // Y
0x00,0x00,0xF8,0x90,0x10,0x20,0x20,0x40,0x48,0xF8,0x00,0x00, // Z
0x00,0x38,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x38,0x00, // [
0x00,0x40,0x40,0x40,0x20,0x20,0x10,0x10,0x10,0x08,0x00,0x00, // <Backslash>
0x00,0x70,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x70,0x00, // ]
0x00,0x20,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ^
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFC, // _
0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // '
0x00,0x00,0x00,0x00,0x00,0x30,0x48,0x38,0x48,0x3C,0x00,0x00, // a
0x00,0x00,0xC0,0x40,0x40,0x70,0x48,0x48,0x48,0x70,0x00,0x00, // b
0x00,0x00,0x00,0x00,0x00,0x38,0x48,0x40,0x40,0x38,0x00,0x00, // c
0x00,0x00,0x18,0x08,0x08,0x38,0x48,0x48,0x48,0x3C,0x00,0x00, // d
0x00,0x00,0x00,0x00,0x00,0x30,0x48,0x78,0x40,0x38,0x00,0x00, // e
0x00,0x00,0x1C,0x20,0x20,0x78,0x20,0x20,0x20,0x78,0x00,0x00, // f
0x00,0x00,0x00,0x00,0x00,0x3C,0x48,0x30,0x40,0x78,0x44,0x38, // g
0x00,0x00,0xC0,0x40,0x40,0x70,0x48,0x48,0x48,0xEC,0x00,0x00, // h
0x00,0x00,0x20,0x00,0x00,0x60,0x20,0x20,0x20,0x70,0x00,0x00, // i
0x00,0x00,0x10,0x00,0x00,0x30,0x10,0x10,0x10,0x10,0x10,0xE0, // j
0x00,0x00,0xC0,0x40,0x40,0x5C,0x50,0x70,0x48,0xEC,0x00,0x00, // k
0x00,0x00,0xE0,0x20,0x20,0x20,0x20,0x20,0x20,0xF8,0x00,0x00, // l
0x00,0x00,0x00,0x00,0x00,0xF0,0xA8,0xA8,0xA8,0xA8,0x00,0x00, // m
0x00,0x00,0x00,0x00,0x00,0xF0,0x48,0x48,0x48,0xEC,0x00,0x00, // n
0x00,0x00,0x00,0x00,0x00,0x30,0x48,0x48,0x48,0x30,0x00,0x00, // o
0x00,0x00,0x00,0x00,0x00,0xF0,0x48,0x48,0x48,0x70,0x40,0xE0, // p
0x00,0x00,0x00,0x00,0x00,0x38,0x48,0x48,0x48,0x38,0x08,0x1C, // q
0x00,0x00,0x00,0x00,0x00,0xD8,0x60,0x40,0x40,0xE0,0x00,0x00, // r
0x00,0x00,0x00,0x00,0x00,0x78,0x40,0x30,0x08,0x78,0x00,0x00, // s
0x00,0x00,0x00,0x20,0x20,0x70,0x20,0x20,0x20,0x18,0x00,0x00, // t
0x00,0x00,0x00,0x00,0x00,0xD8,0x48,0x48,0x48,0x3C,0x00,0x00, // u
0x00,0x00,0x00,0x00,0x00,0xEC,0x48,0x50,0x30,0x20,0x00,0x00, // v
0x00,0x00,0x00,0x00,0x00,0xA8,0xA8,0x70,0x50,0x50,0x00,0x00, // w
0x00,0x00,0x00,0x00,0x00,0xD8,0x50,0x20,0x50,0xD8,0x00,0x00, // x
0x00,0x00,0x00,0x00,0x00,0xEC,0x48,0x50,0x30,0x20,0x20,0xC0, // y
0x00,0x00,0x00,0x00,0x00,0x78,0x10,0x20,0x20,0x78,0x00,0x00, // z
0x00,0x18,0x10,0x10,0x10,0x20,0x10,0x10,0x10,0x10,0x18,0x00, // {
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10, // |
0x00,0x60,0x20,0x20,0x20,0x10,0x20,0x20,0x20,0x20,0x60,0x00, // }
0x40,0xA4,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ~
}; 

//int fcolorr,fcolorg,fcolorb;
//int bcolorr,bcolorg,bcolorb;
int orient;
int display_model, display_transfer_mode, display_serial_mode;
int fch,fcl,bch,bcl;

typedef struct 
{
	uint8_t* font;
	uint8_t x_size;
	uint8_t y_size;
	uint8_t offset;
	uint8_t numchars;
} _current_font;
 


_current_font cfont;
 uint16_t value_port;
 uint16_t value_port;
void _delay_ms (int t){
 uint32_t dem;
for(;t>0;t--) for(dem=0;dem<168000;dem++);
}
 

void LCD_Writ_Bus( char VH, char VL)
{   
		//GPIO_Write(PORT_DATA,VH);
	 set_gpio_8bit(VH);
		pulse_low(PORT_RW, BIT_RW);
		//GPIO_Write(PORT_DATA,VL);
set_gpio_8bit(VL);	
	pulse_low(PORT_RW, BIT_RW);
}
void _fast_fill_8(int ch, long pix)
{int i;
	long blocks;
//	GPIO_Write(PORT_DATA,ch);
	set_gpio_8bit(ch);
	//set_gpo_on_8bit(ch);
	blocks = pix/16;
	for (i=0; i<blocks; i++)
	{
		pulse_low(PORT_RW, BIT_RW);pulse_low(PORT_RW, BIT_RW);
		pulse_low(PORT_RW, BIT_RW);pulse_low(PORT_RW, BIT_RW);
		pulse_low(PORT_RW, BIT_RW);pulse_low(PORT_RW, BIT_RW);
		pulse_low(PORT_RW, BIT_RW);pulse_low(PORT_RW, BIT_RW);
		pulse_low(PORT_RW, BIT_RW);pulse_low(PORT_RW, BIT_RW);
		pulse_low(PORT_RW, BIT_RW);pulse_low(PORT_RW, BIT_RW);
		pulse_low(PORT_RW, BIT_RW);pulse_low(PORT_RW, BIT_RW);
		pulse_low(PORT_RW, BIT_RW);pulse_low(PORT_RW, BIT_RW);
		pulse_low(PORT_RW, BIT_RW);pulse_low(PORT_RW, BIT_RW);
		pulse_low(PORT_RW, BIT_RW);pulse_low(PORT_RW, BIT_RW);
		pulse_low(PORT_RW, BIT_RW);pulse_low(PORT_RW, BIT_RW);
		pulse_low(PORT_RW, BIT_RW);pulse_low(PORT_RW, BIT_RW);
		pulse_low(PORT_RW, BIT_RW);pulse_low(PORT_RW, BIT_RW);
		pulse_low(PORT_RW, BIT_RW);pulse_low(PORT_RW, BIT_RW);
		pulse_low(PORT_RW, BIT_RW);pulse_low(PORT_RW, BIT_RW);
		pulse_low(PORT_RW, BIT_RW);pulse_low(PORT_RW, BIT_RW);
	}
	if ((pix % 16) != 0)
		for (i=0; i<(pix % 16); i++)
		{
			pulse_low(PORT_RW, BIT_RW);pulse_low(PORT_RW, BIT_RW);
		}
}

void LCD_Write_COM(char VL)  
{   
		cbi(PORT_RS, BIT_RS);
		LCD_Writ_Bus(0x00,VL);
}
void LCD_Write_DATA1(char VH,char VL)
{
		sbi(PORT_RS, BIT_RS);
		LCD_Writ_Bus(VH,VL);
}
void LCD_Write_COM_DATA(char com1,int dat1)
{
     LCD_Write_COM(com1);
     LCD_Write_DATA1(dat1>>8,dat1);
}

void InitLCD(int orientation)
{
	orient=orientation;
	sbi(PORT_RST, BIT_RST);
	_delay_ms(5); 
	cbi(PORT_RST, BIT_RST);
	_delay_ms(15);
	sbi(PORT_RST, BIT_RST);
	_delay_ms(15);
	cbi(PORT_CS, BIT_CS);
	LCD_Write_COM_DATA(0xe5, 0x8000);        
	LCD_Write_COM_DATA(0x00, 0x0001);        
	LCD_Write_COM_DATA(0x01, 0x0100);
	LCD_Write_COM_DATA(0x02, 0x0700);
	LCD_Write_COM_DATA(0x03, 0x1030);
	LCD_Write_COM_DATA(0x04, 0x0000);
	LCD_Write_COM_DATA(0x08, 0x0202);        
	LCD_Write_COM_DATA(0x09, 0x0000);        
	LCD_Write_COM_DATA(0x0A, 0x0000);
	LCD_Write_COM_DATA(0x0C, 0x0000);        
	LCD_Write_COM_DATA(0x0D, 0x0000);        
	LCD_Write_COM_DATA(0x0F, 0x0000);        
	//-----Power On sequence-----------------------        
	LCD_Write_COM_DATA(0x10, 0x0000);        
	LCD_Write_COM_DATA(0x11, 0x0007);        
	LCD_Write_COM_DATA(0x12, 0x0000);        
	LCD_Write_COM_DATA(0x13, 0x0000);        
	_delay_ms(50);
	LCD_Write_COM_DATA(0x10, 0x17B0);        
	LCD_Write_COM_DATA(0x11, 0x0007);        
	_delay_ms(10);
	LCD_Write_COM_DATA(0x12, 0x013A);        
	_delay_ms(10);
	LCD_Write_COM_DATA(0x13, 0x1A00);        
	LCD_Write_COM_DATA(0x29, 0x000c);                
	_delay_ms(10);
	//-----Gamma control-----------------------        
	LCD_Write_COM_DATA(0x30, 0x0000);        
	LCD_Write_COM_DATA(0x31, 0x0505);        
	LCD_Write_COM_DATA(0x32, 0x0004);        
	LCD_Write_COM_DATA(0x35, 0x0006);        
	LCD_Write_COM_DATA(0x36, 0x0707);        
	LCD_Write_COM_DATA(0x37, 0x0105);        
	LCD_Write_COM_DATA(0x38, 0x0002);        
	LCD_Write_COM_DATA(0x39, 0x0707);        
	LCD_Write_COM_DATA(0x3C, 0x0704);        
	LCD_Write_COM_DATA(0x3D, 0x0807);        
	//-----Set RAM area-----------------------        
	LCD_Write_COM_DATA(0x50, 0x0000);
	LCD_Write_COM_DATA(0x51, 0x00EF);
	LCD_Write_COM_DATA(0x52, 0x0000);
	LCD_Write_COM_DATA(0x53, 0x013F);
	LCD_Write_COM_DATA(0x60, 0x2700);
	LCD_Write_COM_DATA(0x61, 0x0001);
	LCD_Write_COM_DATA(0x6A, 0x0000);
	LCD_Write_COM_DATA(0x21, 0x0000);        
	LCD_Write_COM_DATA(0x20, 0x0000);        
	//-----Partial Display Control------------        
	LCD_Write_COM_DATA(0x80, 0x0000);        
	LCD_Write_COM_DATA(0x81, 0x0000);
	LCD_Write_COM_DATA(0x82, 0x0000);
	LCD_Write_COM_DATA(0x83, 0x0000);
	LCD_Write_COM_DATA(0x84, 0x0000);        
	LCD_Write_COM_DATA(0x85, 0x0000);
	//-----Panel Control----------------------
	LCD_Write_COM_DATA(0x90, 0x0010);        
	LCD_Write_COM_DATA(0x92, 0x0000);
	LCD_Write_COM_DATA(0x93, 0x0003);
	LCD_Write_COM_DATA(0x95, 0x0110);
	LCD_Write_COM_DATA(0x97, 0x0000);        
	LCD_Write_COM_DATA(0x98, 0x0000);
	//-----Display on-----------------------        
	LCD_Write_COM_DATA(0x07, 0x0173);        
	_delay_ms(50);
	sbi (PORT_CS, BIT_CS); 
	setColor1(255, 255, 255);
	setBackColor1(0, 0, 0);
	cfont.font=0;
}

void setXY(word x1, word y1, word x2, word y2)
{
	if (orient==LANDSCAPE)
	{
		swap(word, x1, y1);
		swap(word, x2, y2)
		y1=SIZE_Y-y1;
		y2=SIZE_Y-y2;
		swap(word, y1, y2)
	}
	LCD_Write_COM_DATA(0x20,x1);
	LCD_Write_COM_DATA(0x21,y1);
	LCD_Write_COM_DATA(0x50,x1);
	LCD_Write_COM_DATA(0x52,y1);
	LCD_Write_COM_DATA(0x51,x2);
	LCD_Write_COM_DATA(0x53,y2);
	LCD_Write_COM(0x22); 
}
void clrXY()
{
	if (orient==PORTRAIT)
		setXY(0,0,SIZE_X,SIZE_Y);
	else
		setXY(0,0,SIZE_Y,SIZE_X);
}
void drawRect(int x1, int y1, int x2, int y2)
{
	if (x1>x2)
	{
		swap(int, x1, x2);
	}
	if (y1>y2)
	{
		swap(int, y1, y2);
	}

	drawHLine(x1, y1, x2-x1);
	drawHLine(x1, y2, x2-x1);
	drawVLine(x1, y1, y2-y1);
	drawVLine(x2, y1, y2-y1);
}

void drawRoundRect(int x1, int y1, int x2, int y2)
{
	if (x1>x2)
	{
		swap(int, x1, x2);
	}
	if (y1>y2)
	{
		swap(int, y1, y2);
	}
	if ((x2-x1)>4 && (y2-y1)>4)
	{
		drawPixel(x1+1,y1+1);
		drawPixel(x2-1,y1+1);
		drawPixel(x1+1,y2-1);
		drawPixel(x2-1,y2-1);
		drawHLine(x1+2, y1, x2-x1-4);
		drawHLine(x1+2, y2, x2-x1-4);
		drawVLine(x1, y1+2, y2-y1-4);
		drawVLine(x2, y1+2, y2-y1-4);
	}
}

void fillRect(int x1, int y1, int x2, int y2)
{ int i;
	if (x1>x2)
	{
		swap(int, x1, x2);
	}
	if (y1>y2)
	{
		swap(int, y1, y2);
	}
	else if (fch==fcl)
	{
		cbi(PORT_CS, BIT_CS);
		setXY(x1, y1, x2, y2);
		sbi(PORT_RS, BIT_RS);
		_fast_fill_8(fch,(((long)(x2-x1)+1)*((long)(y2-y1)+1)));
		sbi(PORT_CS, BIT_CS);
	}
	else
	{
		if (orient==PORTRAIT)
		{
			for (i=0; i<((y2-y1)/2)+1; i++)
			{
				drawHLine(x1, y1+i, x2-x1);
				drawHLine(x1, y2-i, x2-x1);
			}
		}
		else
		{
			for (i=0; i<((x2-x1)/2)+1; i++)
			{
				drawVLine(x1+i, y1, y2-y1);
				drawVLine(x2-i, y1, y2-y1);
			}
		}
	}
}

void fillRoundRect(int x1, int y1, int x2, int y2)
{ int i;
	if (x1>x2)
	{
		swap(int, x1, x2);
	}
	if (y1>y2)
	{
		swap(int, y1, y2);
	}

	if ((x2-x1)>4 && (y2-y1)>4)
	{
		for (i=0; i<((y2-y1)/2)+1; i++)
		{
			switch(i)
			{
			case 0:
				drawHLine(x1+2, y1+i, x2-x1-4);
				drawHLine(x1+2, y2-i, x2-x1-4);
				break;
			case 1:
				drawHLine(x1+1, y1+i, x2-x1-2);
				drawHLine(x1+1, y2-i, x2-x1-2);
				break;
			default:
				drawHLine(x1, y1+i, x2-x1);
				drawHLine(x1, y2-i, x2-x1);
			}
		}
	}
}

void drawCircle(int x, int y, int radius)
{
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x1 = 0;
	int y1 = radius;
	cbi(PORT_CS, BIT_CS);
	setXY(x, y + radius, x, y + radius);
	LCD_Write_DATA1(fch,fcl);
	setXY(x, y - radius, x, y - radius);
	LCD_Write_DATA1(fch,fcl);
	setXY(x + radius, y, x + radius, y);
	LCD_Write_DATA1(fch,fcl);
	setXY(x - radius, y, x - radius, y);
	LCD_Write_DATA1(fch,fcl);
 
	while(x1 < y1)
	{
		if(f >= 0) 
		{
			y1--;
			ddF_y += 2;
			f += ddF_y;
		}
		x1++;
		ddF_x += 2;
		f += ddF_x;    
		setXY(x + x1, y + y1, x + x1, y + y1);
		LCD_Write_DATA1(fch,fcl);
		setXY(x - x1, y + y1, x - x1, y + y1);
		LCD_Write_DATA1(fch,fcl);
		setXY(x + x1, y - y1, x + x1, y - y1);
		LCD_Write_DATA1(fch,fcl);
		setXY(x - x1, y - y1, x - x1, y - y1);
		LCD_Write_DATA1(fch,fcl);
		setXY(x + y1, y + x1, x + y1, y + x1);
		LCD_Write_DATA1(fch,fcl);
		setXY(x - y1, y + x1, x - y1, y + x1);
		LCD_Write_DATA1(fch,fcl);
		setXY(x + y1, y - x1, x + y1, y - x1);
		LCD_Write_DATA1(fch,fcl);
		setXY(x - y1, y - x1, x - y1, y - x1);
		LCD_Write_DATA1(fch,fcl);
	}
	sbi(PORT_CS, BIT_CS);
	clrXY();
}

void fillCircle(int x, int y, int radius)
{int y1,x1;
	for( y1=-radius; y1<=0; y1++) 
		for(x1=-radius; x1<=0; x1++)
			if(x1*x1+y1*y1 <= radius*radius) 
			{
				drawHLine(x+x1, y+y1, 2*(-x1));
				drawHLine(x+x1, y-y1, 2*(-x1));
				break;
			}
}

void clrScr()
{
	long i;
	
	cbi(PORT_CS, BIT_CS);
	clrXY();
		sbi(PORT_RS, BIT_RS);
	 if (display_transfer_mode==8)
		_fast_fill_8(0,SIZE);
	else
	{
		for (i=0; i<(SIZE); i++)
		{
				LCD_Writ_Bus(0,0);
		}
	}
	sbi(PORT_CS, BIT_CS);
}

void fillScr1(int r, int g, int b)
{
	word color = ((r&248)<<8 | (g&252)<<3 | (b&248)>>3);
	fillScr2(color);
}

void fillScr2(word color)
{
	long i;
	char ch, cl;
	ch=color>>8;
	cl=color & 0xFF;
	cbi(PORT_CS, BIT_CS);
	clrXY();
	sbi(PORT_RS, BIT_RS);
	 if (ch==cl)
		_fast_fill_8(ch,SIZE);
	else
	{
		for (i=0; i<SIZE; i++)
		{
				LCD_Writ_Bus(ch,cl);
		}
	}
	sbi(PORT_CS, BIT_CS);
}

void setColor1(int r, int g, int b)
{
	fch=((r&248)|g>>5);
	fcl=((g&28)<<3|b>>3);
}

void setColor2(word color)
{
	fch=color>>8;
	fcl=color & 0xFF;
}

word getColor()
{
	return (fch<<8) | fcl;
}

void setBackColor1(int r, int g, int b)
{
	bch=((r&248)|g>>5);
	bcl=((g&28)<<3|b>>3);
}

void setBackColor2(word color)
{
	bch=color>>8;
	bcl=color & 0xFF;
}

word getBackColor()
{
	return (bch<<8) | bcl;
}

void setPixel(word color)
{
	LCD_Write_DATA1((color>>8),(color&0xFF));	// rrrrrggggggbbbbb
}

void drawPixel(int x, int y)
{
	cbi(PORT_CS, BIT_CS);
	setXY(x, y, x, y);
	setPixel((fch<<8)|fcl);
	sbi(PORT_CS, BIT_CS);
	clrXY();
}

void drawLine(int x1, int y1, int x2, int y2)
{
unsigned int	dx;
		short			xstep;
		unsigned int	dy;
		short			ystep;
		int				col, row,t; 
	if (y1==y2)
		drawHLine(x1, y1, x2-x1);
	else if (x1==x2)
		drawVLine(x1, y1, y2-y1);
	else
	{
		dx = (x2 > x1 ? x2 - x1 : x1 - x2);
		xstep =  x2 > x1 ? 1 : -1;
		dy = (y2 > y1 ? y2 - y1 : y1 - y2);
		ystep =  y2 > y1 ? 1 : -1;
    col = x1, row = y1;

		cbi(PORT_CS, BIT_CS);
		if (dx < dy)
		{
		  t = - (dy >> 1);
			while (1)
			{
				setXY (col, row, col, row);
				LCD_Write_DATA1 (fch, fcl);
				if (row == y2)
					return;
				row += ystep;
				t += dx;
				if (t >= 0)
				{
					col += xstep;
					t   -= dy;
				}
			} 
		}
		else
		{
			t = - (dx >> 1);
			while (1)
			{
				setXY (col, row, col, row);
				                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            LCD_Write_DATA1 (fch, fcl);
				if (col == x2)
					return;
				col += xstep;
				t += dy;
				if (t >= 0)
				{
					row += ystep;
					t   -= dx;
				}
			} 
		}
		sbi(PORT_CS, BIT_CS);
		//GPIO_SetBits(GPIOB,GPIO_Pin_4);
	}
	clrXY();
}

void drawHLine(int x, int y, int l)
{ int i;
	if (l<0)
	{
		l = -l;
		x -= l;
	}
	cbi(PORT_CS, BIT_CS);
	setXY(x, y, x+l, y);
	if (fch==fcl)
	{
		sbi(PORT_RS, BIT_RS);
		_fast_fill_8(fch,l);
	}
	else
	{
		for (i=0; i<l+1; i++)
		{
			LCD_Write_DATA1(fch, fcl);
		}
	}
	sbi(PORT_CS, BIT_CS);
	clrXY();
}

void drawVLine(int x, int y, int l)
{int i;
	if (l<0)
	{
		l = -l;
		y -= l;
	}
	cbi(PORT_CS, BIT_CS);
	setXY(x, y, x, y+l);
	if (fch==fcl)
	{
		sbi(PORT_RS, BIT_RS);
		_fast_fill_8(fch,l);
	}
	else
	{
		for (i=0; i<l+1; i++)
		{
			LCD_Write_DATA1(fch, fcl);
		}
	}
	sbi(PORT_CS, BIT_CS);
	clrXY();
}

void printChar(unsigned char c, int x, int y)
{
	unsigned char j,i,ch;
	cbi(PORT_CS, BIT_CS);
	c-=32;
	if (orient==PORTRAIT)
	{
		setXY(x,y,x+7,y+11);
		for(j=12;j>0;j--)
		{
			ch=SmallFont[c][j-1];
		//	ch=pgm_read_int(&SmallFont[c][j-1]);
			for(i=0;i<8;i++)
			{   
				if((ch&(1<<(7-i)))!=0) 
				{
					setPixel((fch<<8)|fcl);
				} 
				else
				{
					setPixel((bch<<8)|bcl);
				}   
			}
		}
	}
	else
	{
		for(j=0;j<12;j++)
		{
			setXY(x,y+j,x+7,y+j);
			ch=	SmallFont[c][12-j];
			//ch=pgm_read_int(&SmallFont[c][12-j]);
				for(i=0;i<8;i++)
				{   
					if((ch&(1<<i))!=0) 
					{
						setPixel((fch<<8)|fcl);
					} 
					else
					{
						setPixel((bch<<8)|bcl);
					}   
				}
		}
	}
	sbi(PORT_CS, BIT_CS);
	clrXY();
}

void rotateChar(int c, int x, int y, int pos, int deg)
{
	int i,j,ch,zz;
	word temp; 
	int newx,newy;
	double radian;
	radian=deg*0.0175;  

	cbi(PORT_CS, BIT_CS);

	temp=((c-cfont.offset)*((cfont.x_size/8)*cfont.y_size))+4;
	for(j=0;j<cfont.y_size;j++) 
	{
		for ( zz=0; zz<(cfont.x_size/8); zz++)
		{
			//ch=pgm_read_int(&cfont.font[temp+zz]);
			ch=			cfont.font[temp+zz];
			for(i=0;i<8;i++)
			{   
				newx=x+(((i+(zz*8)+(pos*cfont.x_size))*cos(radian))-((j)*sin(radian)));
				newy=y+(((j)*cos(radian))+((i+(zz*8)+(pos*cfont.x_size))*sin(radian)));

				setXY(newx,newy,newx+1,newy+1);
				
				if((ch&(1<<(7-i)))!=0)   
				{
					setPixel((fch<<8)|fcl);
				} 
				else  
				{
					setPixel((bch<<8)|bcl);
				}   
			}
		}
		temp+=(cfont.x_size/8);
	}
	sbi(PORT_CS, BIT_CS);
	clrXY();
}

void print1(char *st, int x, int y, int deg)
{
	int stl, i,j;
	stl = strlen(st);
	if (orient==PORTRAIT)
	{
	if (x==RIGHT)
		x=(SIZE_X+1)-(stl*8);
	if (x==CENTER)
		x=((SIZE_X+1)-(stl*8))/2;
	}
	else
	{
	if (x==RIGHT)
		x=(SIZE_Y+1)-(stl*8);
	if (x==CENTER)
		x=((SIZE_Y+1)-(stl*8))/2;
	}
j=0;
	for (i=0; i<stl; i++){
		if(*st=='\n') {
x=10; y-=10;
	j=i;	
} 
	if (deg==0)			
			printChar(*st++, x + (i-j)*8, y);
		else
			rotateChar(*st++, x, y, i, deg);
							}
}
void setFont(uint8_t* font)
{
	cfont.font=font;
	cfont.x_size=font[0];
	cfont.y_size=font[1];
	cfont.offset=font[2];
	cfont.numchars=font[3];
}

uint8_t* getFont()
{
	return cfont.font;
}
uint8_t getFontXsize()
{
	return cfont.x_size;
}

uint8_t getFontYsize()
{
	return cfont.y_size;
}

void drawBitmap1(int x, int y, int sx, int sy, bitmapdatatype data, int scale)
{
	unsigned int col;
	long temp;
	int tx, ty;
	int i,j;
	temp=sx*sy;
	if (scale==1)
	{
		if (orient==PORTRAIT)
		{
				cbi(PORT_CS, BIT_CS);
				setXY(x, y, x+sx-1, y+sy-1);
				for(i=0;i<sy;i++)
				{
					for(j=sx;j>0;j--)
					{
					col=data[temp-(i*sx+j)-1];
						//col=pgm_read_word(&data[temp-(i*sx+j)-1]);
					LCD_Write_DATA1(col>>8,col & 0xff);
				}
			}
			sbi(PORT_CS, BIT_CS);
		}
		else
		{
			cbi(PORT_CS, BIT_CS);
			for (ty=0; ty<sy; ty++)
			{
				setXY(x, y+ty, x+sx-1, y+ty);
				for (tx=sx-1; tx>=0; tx--)
				{
				//	col=pgm_read_word(&data[temp-(ty*sx)+tx]);
					col=data[temp-(ty*sx)+tx];
					LCD_Write_DATA1(col>>8,col & 0xff);

				}
			}
			sbi(PORT_CS, BIT_CS);
		}
	}
	/*else
	{
		if (orient==PORTRAIT)
		{
			cbi(PORT_CS, BIT_CS);
			for (ty=0; ty<sy; ty++)
			{
				setXY(x, y+(ty*scale), x+((sx*scale)-1), y+(ty*scale)+scale);
				for (tsy=0; tsy<scale; tsy++)
					for (tx=0; tx<sx; tx++)
					{
						col=pgm_read_word(&data[(ty*sx)+tx]);
						for (tsx=0; tsx<scale; tsx++)
							LCD_Write_DATA1(col>>8,col & 0xff);
					}
			}
			sbi(PORT_CS, BIT_CS);
		}
		else
		{
			cbi(PORT_CS, BIT_CS);
			for (ty=0; ty<sy; ty++)
			{
				for (tsy=0; tsy<scale; tsy++)
				{
					setXY(x, y+(ty*scale)+tsy, x+((sx*scale)-1), y+(ty*scale)+tsy);
					for (tx=sx; tx>=0; tx--)
					{
						col=pgm_read_word(&data[(ty*sx)+tx]);
						for (tsx=0; tsx<scale; tsx++)
							LCD_Write_DATA1(col>>8,col & 0xff);
					}
				}
			}
			sbi(PORT_CS, BIT_CS);
		}
	}*/
	clrXY();
}

void drawBitmap2(int x, int y, int sx, int sy, bitmapdatatype data, int deg, int rox, int roy)
{
	unsigned int col;
	int tx, ty, newx, newy;
	double radian;
	radian=deg*0.0175;  

	if (deg==0)
		drawBitmap1(x, y, sx, sy, data,1);
	else
	{
		cbi(PORT_CS, BIT_CS);
		for (ty=0; ty<sy; ty++)
			for (tx=0; tx<sx; tx++)
			{
			//	col=pgm_read_word(&data[(ty*sx)+tx]);
				col=data[(ty*sx)+tx];
				newx=x+rox+(((tx-rox)*cos(radian))-((ty-roy)*sin(radian)));
				newy=y+roy+(((ty-roy)*cos(radian))+((tx-rox)*sin(radian)));
				setXY(newx, newy, newx, newy);
				LCD_Write_DATA1(col>>8,col & 0xff);
			}
		sbi(PORT_CS, BIT_CS);
	}
	clrXY();
}
int getDisplayXSize()
{
	if (orient==PORTRAIT)
		return SIZE_X+1;
	else
		return SIZE_Y+1;
}

int getDisplayYSize()
{
	if (orient==PORTRAIT)
		return SIZE_Y+1;
	else
		return SIZE_X+1;
}
//void print1(char *st, int x, int y, int deg)
void display_tex_theododai(int ma,int dodai,char* st){

	int stl, i,j;
	char deg;
	int x,y;
	
	deg=0;
	x=10;y=230;
	stl = dodai;//strlen(st);
	if (orient==PORTRAIT)
	{
	if (x==RIGHT)
		x=(SIZE_X+1)-(stl*8);
	if (x==CENTER)
		x=((SIZE_X+1)-(stl*8))/2;
	}
	else
	{
	if (x==RIGHT)
		x=(SIZE_Y+1)-(stl*8);
	if (x==CENTER)
		x=((SIZE_Y+1)-(stl*8))/2;
	}
j=0;
	for (i=0; i<stl; i++){
if((i%32)==31)			
		{
x=10; y-=10;
	j=i;	
} 

	if (deg==0)			
			printChar(*st++, x + (i-j)*8, y);
		else
			rotateChar(*st++, x, y, i, deg);
							}
}


//cainatdocuongthietke

void drawfige(uint8_t* pat)
{
unsigned int col;
	long temp;
	int tx, ty,lx,ly;
	int i,j;
	temp=100*100;
		{
					col=0xf43d;
			cbi(PORT_CS, BIT_CS);
				for (tx=0; tx<300; tx++)
				{ ty=pat[tx];
					lx=tx+10;
					ly=ty+10;
			  	setXY(lx, ly, lx,ly);
					LCD_Write_DATA1(col>>8,col & 0xff);
			}
			sbi(PORT_CS, BIT_CS);
		}
	
	
	clrXY();
}

void drawfige_e(uint8_t* pat)
{
unsigned int col;
	long temp;
	int tx, ty,lx,ly;
	int i,j;
	temp=100*100;
		{
					col=VGA_WHITE;
			cbi(PORT_CS, BIT_CS);
				for (tx=0; tx<300; tx++)
				{ ty=pat[tx];
					lx=tx+10;
					ly=ty+10;
			  	setXY(lx, ly, lx,ly);
					LCD_Write_DATA1(col>>8,col & 0xff);
			}
			sbi(PORT_CS, BIT_CS);
		}
	
	
	clrXY();
}


void drawfige_cx(int x,uint8_t pat)
{
unsigned int col;
	long temp;
	int y;
	temp=100*100;
		{
			cbi(PORT_CS, BIT_CS);
				{ y=pat;
			  	setXY(x,y,x,y);
					col=0xac78;
					LCD_Write_DATA1(col>>8,col & 0xff);
			}
			sbi(PORT_CS, BIT_CS);
		}
	
	clrXY();
}

