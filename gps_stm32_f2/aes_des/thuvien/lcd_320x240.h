#ifndef __DIEUKHIEN_H
#define __DIEUKHIEN_H

#include <stm32f4xx.h>

//#include "HW_AVR_defines.h"
//#include "memorysaver.h"
#include <stdio.h>
//#include "var.h"
//#include "font.h"
//#include "anh.h"
//#include "Logo.h"

#define DISABLE_HX8347A			1	// ITDB32
#define DISABLE_ILI9327			1	// ITDB32WC / TFT01_32W
#define DISABLE_SSD1289			1	// ITDB32S / TFT_32 / GEEE32 / INFINIT32	- This single define will disable both normal and latched mode for this controller
#define DISABLE_ILI9325C  		1	// ITDB24
#define DISABLE_ILI9325D  		1	// ITDB24D / ITDB24DWOT / ITDB28 / TFT01_24_8 / TFT01_24_16	- This single define will disable both 8bit and 16bit mode for this controller
#define DISABLE_HX8340B_8 		1	// ITDB22 8bit mode / GEEE22
#define DISABLE_HX8340B_S 		1	// ITDB22 Serial mode
#define DISABLE_HX8352A			1	// ITDB32WD / TFT01_32WD
#define DISABLE_ST7735			1	// ITDB18SP
#define DISABLE_PCF8833			1	// LPH9135
#define DISABLE_S1D19122  		1	// ITDB25H
#define DISABLE_SSD1963_480		1	// ITDB43
#define DISABLE_SSD1963_800		1	// ITDB50
#define DISABLE_S6D1121			1	// ITDB24E	

#define cbi(port, bit) GPIO_ResetBits(port,bit) // (port)&= ~(0x01<<bit)  
#define sbi(port, bit) GPIO_SetBits(port,bit) // (port) |= (0x01<<bit)
#define pulse_high(reg, bitmask) sbi(reg, bitmask); cbi(reg, bitmask);
#define pulse_low(reg, bitmask) cbi(reg, bitmask); sbi(reg, bitmask);

#define cport(port, data) port &= data
#define sport(port, data) port |= data

#define swap(type, i, j) {type t = i; i = j; j = t;}

//#define fontbyte(x) pgm_read_byte(&cfont.font[x])  

#define regtype volatile uint8_t
#define regsize uint8_t
#define bitmapdatatype unsigned int*

typedef int word;
typedef unsigned char uint8_t;
#define PORT_SDA  GPIOA
#define PORT_SCL  GPIOA

#define PORT_ALE     GPIOB

#define PORT_RS	  GPIOB
#define PORT_RW   GPIOB
#define PORT_CS    GPIOA
#define PORT_RST  GPIOC
#define PORT_RD   GPIOB

#define BIT_ALE     GPIO_Pin_0


#define BIT_RS       GPIO_Pin_8
#define BIT_RW      GPIO_Pin_7
#define BIT_RD     GPIO_Pin_5
#define BIT_CS       GPIO_Pin_8
#define BIT_RST     GPIO_Pin_6

#define BIT_SDA     GPIO_Pin_0
#define BIT_SCL     GPIO_Pin_1

#define PORT_DATA GPIOD


#define false 0
#define true  1
#define boolean char
//#define pgm_read_int(a) pgm_read_byte(a) 
//#define pgm_read_int(a) pgm_read_word(a) 


#define LEFT 0
#define RIGHT 9999
#define CENTER 9998

#define PORTRAIT 0
#define LANDSCAPE 1

#define HX8347A			0
#define ILI9327			1
#define SSD1289			2
#define ILI9325C		3
#define ILI9325D_8		4
#define ILI9325D_16		5
#define HX8340B_8		6
#define HX8340B_S		7
#define HX8352A			8
#define ST7735			9
#define PCF8833			10
#define S1D19122		11
#define SSD1963_480		12
#define SSD1963_800		13
#define S6D1121_8		14
#define S6D1121_16		15
#define	SSD1289LATCHED	16
#define ILI9320_8		17
#define ILI9320_16		18

#define ITDB32			0	// HX8347-A (16bit)
#define ITDB32WC		1	// ILI9327  (16bit)
#define TFT01_32W		1	// ILI9327	(16bit)
#define ITDB32S			2	// SSD1289  (16bit)
#define TFT01_32		2	// SSD1289  (16bit)
#define GEEE32			2	// SSD1289  (16bit)
#define ITDB24			3	// ILI9325C (8bit)
#define ITDB24D			4	// ILI9325D (8bit)
#define ITDB24DWOT		4	// ILI9325D (8bit)
#define ITDB28			4	// ILI9325D (8bit)
#define TFT01_24_8		4	// ILI9325D (8bit)
#define TFT01_24_16		5	// ILI9325D (16bit)
#define ITDB22			6	// HX8340-B (8bit)
#define GEEE22			6	// HX8340-B (8bit)
#define ITDB22SP		7	// HX8340-B (Serial)
#define ITDB32WD		8	// HX8352-A (16bit)
#define TFT01_32WD		8	// HX8352-A	(16bit)
#define ITDB18SP		9	// ST7735   (Serial)
#define LPH9135			10	// PCF8833	(Serial)
#define ITDB25H			11	// S1D19122	(16bit)
#define ITDB43			12	// SSD1963	(16bit) 480x272
#define ITDB50			13	// SSD1963	(16bit) 800x480
#define ITDB24E_8		14	// S6D1121	(8bit)
#define ITDB24E_16		15	// S6D1121	(16bit)
#define INFINIT32		16	// SSD1289	(Latched 16bit)
#define GEEE24			17	// ILI9320	(8bit)
#define GEEE28			18	// ILI9320	(16bit)

#define SERIAL_4PIN		4
#define SERIAL_5PIN		5
#define LATCHED_16		17

#define SIZE	76800
#define SIZE_X 240
#define SIZE_Y 320
//*********************************
// COLORS
//*********************************
// VGA color palette
#define VGA_BLACK		0x0000
#define VGA_WHITE		0xFFFF
#define VGA_RED			0xF800
#define VGA_GREEN		0x0400
#define VGA_BLUE		0x001F
#define VGA_SILVER		0xC618
#define VGA_GRAY		0x8410
#define VGA_MAROON		0x8000
#define VGA_YELLOW		0xFFE0
#define VGA_OLIVE		0x8400
#define VGA_LIME		0x07E0
#define VGA_AQUA		0x07FF
#define VGA_TEAL		0x0410
#define VGA_NAVY		0x0010
#define VGA_FUCHSIA		0xF81F
#define VGA_PURPLE		0x8010



#define swap(type, i, j) {type t = i; i = j; j = t;}

//#define fontbyte(x) pgm_read_byte(&cfont.font[x])  

#define regtype volatile uint8_t
#define regsize uint8_t
#define bitmapdatatype unsigned int*






 #define swap(type, i, j) {type t = i; i = j; j = t;}
    void _delay_ms (int t);
		void LCD_Writ_Bus(char VH,char VL);
		void LCD_Write_COM(char VL);
		void LCD_Write_DATA1(char VH,char VL);
		void LCD_Write_COM_DATA(char com1,int dat1);
		void InitLCD(int orientation);
		void fillScr1(int r, int g, int b);
		void fillScr2(word color);
		void fillCircle(int x, int y, int radius);
		void fillRect(int x1, int y1, int x2, int y2);
		void setColor1(int r, int g, int b);
		void setColor2(word color);
		word getColor(void);
		void setBackColor1(int r, int g, int b);
		void setBackColor2(word color);
		word getBackColor(void);
		void drawRect(int x1, int y1, int x2, int y2);
		void drawHLine(int x, int y, int l);
		void drawVLine(int x, int y, int l);
		void clrScr(void);
		void drawPixel(int x, int y);
		void drawLine(int x1, int y1, int x2, int y2);
		void drawRoundRect(int x1, int y1, int x2, int y2);
		void fillRoundRect(int x1, int y1, int x2, int y2);
		void drawCircle(int x, int y, int radius);
		void print1(char *st, int x, int y, int deg);
		void setFont(uint8_t* font);
		uint8_t* getFont(void);
		uint8_t getFontXsize1(void);
		uint8_t getFontYsize2(void);
		void drawBitmap1(int x, int y, int sx, int sy, bitmapdatatype data, int scale);
		void drawBitmap2(int x, int y, int sx, int sy, bitmapdatatype data, int deg, int rox, int roy);
		int  getDisplayXSize(void);
		int	 getDisplayYSize(void);
		void setPixel(word color);
		void printChar(unsigned char c, int x, int y);
		void setXY(word x1, word y1, word x2, word y2);
		void clrXY(void);
		void rotateChar(int c, int x, int y, int pos, int deg);
		void _fast_fill_8(int ch, long pix);


#endif

