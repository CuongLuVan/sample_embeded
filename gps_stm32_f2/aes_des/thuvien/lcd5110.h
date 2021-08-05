
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

/*********** PORTA ************/



#define NOKIA5110_X_SIZE                                  84
#define NOKIA5110_Y_SIZE                                  48
#define NOKIA5110_Y_ARRAY_SIZE                            (NOKIA5110_Y_SIZE/8)
#define NOKIA5110_DATA_SELECT                             1
#define NIKIA5110_COMMAND_SELECT                          0
#define NIKIA5110_FUNCTION_VERTICAL_BA                    0x22  //Lenh co ban, va dung che do doc
#define NIKIA5110_FUNCTION_VERTICAL_EX                    0x23  //Lenh them, va dung che do doc
#define NIKIA5110_FUNCTION_HORIZONTA_BA                   0x20	//Lenh co ban, va dung che do ngang
#define NIKIA5110_FUNCTION_HORIZONTA_EX                   0x21  //Lenh them, va dung che do ngang
#define NIKIA5110_DISPLAY_BLANK                           0x08  // Nhap nhay con tro 
#define NIKIA5110_DISPLAY_ALL_ON                          0x09  // Bat tat ca cac segment
#define NIKIA5110_DISPLAY_NORMAL                          0x0d  // Che do binh thuong  
#define NIKIA5110_DISPLAY_IN_VIDEO                        0x0D  // Che do chuyen doi Video      
#define NOKIA5110_X_ADDRESS                               0x40        
#define NOKIA5110_Y_ADDRESS                               0x80                             
 /*******************************************************************************
Noi Dung    :   Gui 1 Byte du lieu den Nokia5110
Tham Bien   :   Data     :   Byte du lieu.
Tra Ve      :   Khong.
********************************************************************************/
void setup_nokia(void);

void NOKIA5110_WriteData(uint8_t Data);

 /*******************************************************************************
Noi Dung    :   Gui 1 Byte du lieu den Nokia5110
Tham Bien   :   Command    :   Byte lenh.
Tra Ve      :   Khong.
********************************************************************************/

void NOKIA5110_WriteCommand(uint8_t Command);

 /*******************************************************************************
Noi Dung    :   Khoi tao LCD NOKIA 5110.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
********************************************************************************/

void NOKIA5110_Init(void);

 /*******************************************************************************
Noi Dung    :   Thiet lap vi tri con tro LCD NOKIA 5110.
Tham Bien   :   x: vi tri cot cua con tro. x = 0 - 83.
                y: vi tri hang cua con tro. y= 0-5.
Tra Ve      :   Khong.
********************************************************************************/

void NOKIA5110_GotoXY(uint8_t X, uint8_t Y);

 /*******************************************************************************
Noi Dung    :   Xoa noi dung hien thi tren LCD Nokia 5110.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
********************************************************************************/

void NOKIA5110_Clear(void);

 /*******************************************************************************
Noi Dung    :   Viet 1 ki tu len LCD Nokia 5110.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
********************************************************************************/

void NOKIA5110_PutChar(uint8_t C);

 /*******************************************************************************
Noi Dung    :   Viet 1 chuoi ki tu len LCD Nokia 5110.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
********************************************************************************/

void NOKIA5110_Puts(uint8_t *s);
//void NOKIA5110_SHIFT_STRING(uint8_t *s, uint8_t x, uint8_t y);
