#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define GPIO_80 GPIOB
#define GPIO_81 GPIOB
#define GPIO_82 GPIOB
#define GPIO_83 GPIOB
#define GPIO_84 GPIOB
#define GPIO_85 GPIOB
#define GPIO_86 GPIOB
#define GPIO_87 GPIOB

#define GPIO_ON GPIOB
#define GPIO_PIN80 GPIO_Pin_0  
#define GPIO_PIN81 GPIO_Pin_1 
#define GPIO_PIN82 GPIO_Pin_2 
#define GPIO_PIN83 GPIO_Pin_10 
#define GPIO_PIN84 GPIO_Pin_11 
#define GPIO_PIN85 GPIO_Pin_12 
#define GPIO_PIN86 GPIO_Pin_13 
#define GPIO_PIN87 GPIO_Pin_14

#define LCD 1
#define off_device 0


// pe14 pb10 pb12 pb14 pd8     pd10 pd12 pd14 pc6    pc8 pa8 pa10 pa12            pa14 pc10 pc12 

void set_gpo_on_8bit(uint16_t value);
void set_gpio_8bit(uint8_t value);
void choice_device(void);
void notchoice_device(void);
//void set_gpio_16bit(uint16_t value);
