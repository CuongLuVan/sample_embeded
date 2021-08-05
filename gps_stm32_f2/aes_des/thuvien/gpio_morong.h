#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

#define GPIO_80 GPIOD
#define GPIO_81 GPIOD
#define GPIO_82 GPIOD
#define GPIO_83 GPIOD
#define GPIO_84 GPIOC
#define GPIO_85 GPIOA
#define GPIO_86 GPIOC
#define GPIO_87 GPIOC

#define GPIO_ON GPIOD
#define GPIO_PIN80 GPIO_Pin_1  
#define GPIO_PIN81 GPIO_Pin_6 
#define GPIO_PIN82 GPIO_Pin_2 
#define GPIO_PIN83 GPIO_Pin_0 
#define GPIO_PIN84 GPIO_Pin_11 
#define GPIO_PIN85 GPIO_Pin_15 
#define GPIO_PIN86 GPIO_Pin_8 
#define GPIO_PIN87 GPIO_Pin_9

#define LCD 1
#define off_device 0


// pe14 pb10 pb12 pb14 pd8     pd10 pd12 pd14 pc6    pc8 pa8 pa10 pa12            pa14 pc10 pc12 

void set_gpo_on_8bit(uint16_t value);
void set_gpio_8bit(uint8_t value);
void choice_device(void);
void notchoice_device(void);
//void set_gpio_16bit(uint16_t value);
