
#include "gpio_morong.h"
// neu 8 bit lien tiep nhau
void set_gpo_on_8bit(uint16_t value){
uint16_t readon;
	readon=GPIO_ReadOutputData(GPIO_ON);
	readon=(readon&0xff00)|(value&0x00ff);
	GPIO_Write(GPIO_ON,readon);
}

void set_gpio_8bit(uint8_t value){
	
if((value&0x80)!=0) GPIO_SetBits(GPIO_87, GPIO_PIN87); 
	else  GPIO_ResetBits(GPIO_87, GPIO_PIN87);
	
	if((value&0x40)!=0) GPIO_SetBits(GPIO_86, GPIO_PIN86); 
	else  GPIO_ResetBits(GPIO_86, GPIO_PIN86);
	
	if((value&0x20)!=0) GPIO_SetBits(GPIO_85, GPIO_PIN85); 
	else  GPIO_ResetBits(GPIO_85, GPIO_PIN85);
	
	if((value&0x10)!=0) GPIO_SetBits(GPIO_84, GPIO_PIN84); 
	else  GPIO_ResetBits(GPIO_84, GPIO_PIN84);
	
	if((value&0x08)!=0) GPIO_SetBits(GPIO_83, GPIO_PIN83); 
	else  GPIO_ResetBits(GPIO_83, GPIO_PIN83);
	
	if((value&0x04)!=0) GPIO_SetBits(GPIO_82, GPIO_PIN82); 
	else  GPIO_ResetBits(GPIO_82, GPIO_PIN82);
	
	if((value&0x02)!=0) GPIO_SetBits(GPIO_81, GPIO_PIN81); 
	else  GPIO_ResetBits(GPIO_81, GPIO_PIN81);
	
	if((value&0x01)!=0) GPIO_SetBits(GPIO_80, GPIO_PIN80); 
	else  GPIO_ResetBits(GPIO_80, GPIO_PIN80);


}
void choice_device(void){
	//pc4 pc5
	GPIO_SetBits(GPIOC, GPIO_PIN84);
	GPIO_ResetBits(GPIOC, GPIO_PIN85);
}
void notchoice_device(void){
	//pc4 pc5
	GPIO_SetBits(GPIOC, GPIO_PIN84);
	GPIO_SetBits(GPIOC, GPIO_PIN85);
}


