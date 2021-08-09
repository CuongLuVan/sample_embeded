#include "stm32f10x.h"
#include "stm32f10x_gpio.h"


 uint32_t timer,timerset,timercount;
 uint16_t doam,light,count_history,auto_doam,auto_doamdat,auto_temp,auto_light;
 uint16_t time_second,time_mun,time_hour,time_set_mun,time_set_hour;
 uint8_t  warning,water,temph;
extern uint8_t temp;



void show_Two_Digit(uint32_t nCount){
uint32_t number1;
char a[3];
a[2]='\0';	
number1=(nCount%10)+48;
a[1]=number1;	
number1=(nCount/10);
number1=(number1%10)+48;	
a[0]=number1;
NOKIA5110_Puts(a);
}
void show_Four_Digit(uint32_t nCount){
uint32_t number1,number2;
char a[5];
a[4]='\0';	
number1=(nCount%10)+48;
a[3]=number1;	
number2=(nCount/10);
number1=(number2%10)+48;	
a[2]=number1;
number2=(nCount/10);
number1=(number2%10)+48;	
a[1]=number1;
number2=(nCount/10);
number1=(number2%10)+48;	
a[0]=number1;	
NOKIA5110_Puts(a);
}


void interface_Start(void){

	NOKIA5110_Clear();
					NOKIA5110_GotoXY(0,0);
        NOKIA5110_Puts("TIME"); 
          NOKIA5110_GotoXY(0,1);
        show_two_digit(timer);
}



void interface(void){
	NOKIA5110_Clear();
	NOKIA5110_GotoXY(0,0);
Time_Display(RTC_GetCounter());

}
// giao dien thoi gian
// ung dung the hien, hien thi thoi gian
void interface_Time(void){
					NOKIA5110_Clear();
					NOKIA5110_GotoXY(0,0);
        NOKIA5110_Puts("SET UP THE TIME"); 
          NOKIA5110_GotoXY(0,1);
	time_set_mun=time_mun;
	time_set_hour=time_hour;
	
}
void interface_time_chage(void){
          NOKIA5110_Clear();
					NOKIA5110_GotoXY(0,0);
          NOKIA5110_Puts("SET UP TO CHANGE THE TIME"); 
          NOKIA5110_GotoXY(0,1);
          Time_Display(time_set_hour*3600+time_set_mun*60);
}


void interface_time_ok(void){
 RTC_SetCounter(time_set_hour*3600+time_set_mun*60);
}
void interface_timeh_up(void){
NOKIA5110_GotoXY(0,1);	
	time_set_hour++;
	if(time_set_hour>23) time_set_hour=0;
Time_Display(time_set_hour*3600+time_set_mun*60);
}
void interface_timeh_down(void){
NOKIA5110_GotoXY(0,1);	
	time_set_hour--;
	if((time_set_hour==0)&&(time_set_hour>23)) time_set_hour=23;
Time_Display(time_set_hour*3600+time_set_mun*60);
}
void interface_timem_up(void){
NOKIA5110_GotoXY(0,1);	
	time_set_mun++;
	if((time_set_hour>59)) time_set_mun=0;
Time_Display(time_set_hour*3600+time_set_mun*60);	
}
void interface_timem_down(void){
NOKIA5110_GotoXY(0,1);	
	time_set_mun--;
	if((time_set_mun==0)&&(time_set_mun>59)) time_set_hour=59;
Time_Display(time_set_hour*3600+time_set_mun*60);
}

// giaodien chinh sua do am khong khi
void interface_humidity (void){
           NOKIA5110_Clear();
					NOKIA5110_GotoXY(0,0);
        NOKIA5110_Puts("SET UP FOR humidity"); 
}
void interface_setup_humidity(void){
             NOKIA5110_Clear();
					NOKIA5110_GotoXY(0,0);
        NOKIA5110_Puts("humidity"); 
}
void interface_doam_set(void){
 NOKIA5110_Clear();
					NOKIA5110_GotoXY(0,0);
        NOKIA5110_Puts("humidity have been set up"); 
NOKIA5110_GotoXY(0,1);
	show_two_digit(doam);
	NOKIA5110_Puts("auto:");
	if(auto_doam==0) NOKIA5110_Puts("off"); else NOKIA5110_Puts("on");
}
void interface_setup_humidity_up(void){
NOKIA5110_GotoXY(0,1);
	if(doam>100) doam=0; else doam++;
show_two_digit(doam);
}
void interface_setup_humidity_down(void){
NOKIA5110_GotoXY(0,1);
	if(doam>100) doam=0; else doam--;
show_two_digit(doam);
}
void interface_setup_humidity_on(void){
NOKIA5110_GotoXY(0,2);
if(auto_doam==0) {NOKIA5110_Puts("on "); doam=1;  }else {NOKIA5110_Puts("off"); doam=0;}
}
void interface_setup_humidity_off(void){
NOKIA5110_GotoXY(0,2);
if(auto_doam==0) {NOKIA5110_Puts("on "); doam=1;  }else {NOKIA5110_Puts("off"); doam=0;}
}

// thiet lap do am cua dat
void interface_doamdat(void){
NOKIA5110_Clear();
					NOKIA5110_GotoXY(0,0);
        NOKIA5110_Puts("SET UP FOR land humidity "); 
}
void interface_setup_doamdat(void){
 NOKIA5110_Clear();
					NOKIA5110_GotoXY(0,0);
        NOKIA5110_Puts("land humidity set up"); 
NOKIA5110_GotoXY(0,1);
	NOKIA5110_Puts("auto:");
	if(auto_doamdat==0) NOKIA5110_Puts("off"); else NOKIA5110_Puts("on ");
}

interface_doam_datset(void){
NOKIA5110_Clear();
					NOKIA5110_GotoXY(0,0);
        NOKIA5110_Puts("land humidity have been set up"); 
NOKIA5110_GotoXY(0,1);
	NOKIA5110_Puts("auto:");
	if(auto_doamdat==0) NOKIA5110_Puts("off"); else NOKIA5110_Puts("on ");
}
void interface_setup_doam_daton(void){
NOKIA5110_GotoXY(0,1);
	NOKIA5110_Puts("auto:");
	if(auto_doamdat==0) {NOKIA5110_Puts("on "); auto_doamdat=1; } else {NOKIA5110_Puts("off"); auto_doamdat=0; }
}
void interface_setup_doam_datoff(void){
NOKIA5110_GotoXY(0,1);
	NOKIA5110_Puts("auto:");
	if(auto_doamdat==0) {NOKIA5110_Puts("on "); auto_doamdat=1; } else {NOKIA5110_Puts("off"); auto_doamdat=0; }
}

// diau chinh nhiet do
void interface_temp(void){
NOKIA5110_Clear();
					NOKIA5110_GotoXY(0,0);
        NOKIA5110_Puts("SET UP FOR TEMPERATURE "); 
}
void interface_setup_temp(void){
NOKIA5110_Clear();
					NOKIA5110_GotoXY(0,0);
        NOKIA5110_Puts("TEMPERATURE  set up"); 
NOKIA5110_GotoXY(0,1);
	show_two_digit(temph);
	NOKIA5110_GotoXY(0,2);
	NOKIA5110_Puts("auto:");
	if(auto_doam==0) NOKIA5110_Puts("off"); else NOKIA5110_Puts("on");

}
void interface_temp_set(void){
NOKIA5110_Clear();
					NOKIA5110_GotoXY(0,0);
        NOKIA5110_Puts("TEMPERATURE have been set up"); 
NOKIA5110_GotoXY(0,1);
	show_two_digit(temph);
	NOKIA5110_GotoXY(0,2);
	NOKIA5110_Puts("auto:");
	if(auto_doam==0) NOKIA5110_Puts("off"); else NOKIA5110_Puts("on");
}
void interface_setup_tempup(void){
NOKIA5110_GotoXY(0,1);
	if(temph>99)  temph=0; else temph++;
	show_two_digit(temph);
}
void interface_setup_tempdown(void){
NOKIA5110_GotoXY(0,1);
	if(temph<1)  temph++; else temph--;
	show_two_digit(temph);
}
void interface_setup_tempon(void){
NOKIA5110_GotoXY(0,2);
	NOKIA5110_Puts("auto:");
	if(auto_temp==0) {NOKIA5110_Puts("on "); auto_temp=1; } else {NOKIA5110_Puts("off"); auto_temp=0;}
}
void interface_setup_tempoff(void){
NOKIA5110_GotoXY(0,1);
		NOKIA5110_Puts("auto:");
	if(auto_temp==0) {NOKIA5110_Puts("on "); auto_temp=1; } else {NOKIA5110_Puts("off"); auto_temp=0;}
}

// dieu ching anh sang

void interface_light(void){
NOKIA5110_Clear();
					NOKIA5110_GotoXY(0,0);
        NOKIA5110_Puts("SET UP FOR light "); 
}
void interface_setup_light(void){
NOKIA5110_Clear();
					NOKIA5110_GotoXY(0,0);
        NOKIA5110_Puts("light  set up"); 
NOKIA5110_GotoXY(0,1);
	show_for_digit(light);
	NOKIA5110_GotoXY(0,2);
	NOKIA5110_Puts("auto:");
	if(auto_light==0) NOKIA5110_Puts("off"); else NOKIA5110_Puts("on");

}
void interface_light_set(void){
NOKIA5110_Clear();
					NOKIA5110_GotoXY(0,0);
        NOKIA5110_Puts("TEMPERATURE have been set up"); 
NOKIA5110_GotoXY(0,1);
	show_for_digit(light);
	NOKIA5110_GotoXY(0,2);
	NOKIA5110_Puts("auto:");
	if(auto_light==0) NOKIA5110_Puts("off"); else NOKIA5110_Puts("on");
}
void interface_setup_lightup(void){
NOKIA5110_GotoXY(0,1);
	if(light>4000)  light=0; else light++;
	show_for_digit(light);
}
void interface_setup_lightdown(void){
NOKIA5110_GotoXY(0,1);
	if(light<1)  light=4000; else light--;
	show_for_digit(light);
}
void interface_setup_lighton(void){
NOKIA5110_GotoXY(0,2);
	NOKIA5110_Puts("auto:");
	if(auto_light==0) {NOKIA5110_Puts("on "); auto_light=1; } else {NOKIA5110_Puts("off"); auto_light=0;}
}
void interface_setup_lightoff(void){
NOKIA5110_GotoXY(0,1);
		NOKIA5110_Puts("auto:");
	if(auto_light==0) {NOKIA5110_Puts("on "); auto_light=1; } else {NOKIA5110_Puts("off"); auto_light=0;}
}

//  lich su luu lai


void interface_history(void){
NOKIA5110_Clear();
					NOKIA5110_GotoXY(0,0);
        NOKIA5110_Puts("READ HISTORY"); 
}
void interface_read_history(void){
            NOKIA5110_Clear();
        	NOKIA5110_GotoXY(0,0);
        NOKIA5110_Puts("HISTORY");
}
void interface_read_history_on_next(void){
NOKIA5110_Clear();
        	NOKIA5110_GotoXY(0,0);
        NOKIA5110_Puts("HISTORY");
}
	
	// bao chu y, bao daong
	
void interface_warning(void){
NOKIA5110_Clear();
        	NOKIA5110_GotoXY(0,0);
        NOKIA5110_Puts("setup warning");
}
void interface_setup_warnig(void){
					 NOKIA5110_Clear();
        	NOKIA5110_GotoXY(0,0);
        NOKIA5110_Puts("setup warning");
	NOKIA5110_GotoXY(0,1);
	NOKIA5110_Puts("warning");
	if(warning==0) {NOKIA5110_Puts("on "); } else {NOKIA5110_Puts("off"); }
NOKIA5110_GotoXY(0,2);
NOKIA5110_Puts("water");
	if(water==0) {NOKIA5110_Puts("on "); } else {NOKIA5110_Puts("off");}
}
void interface_setup_warning_on(void){
					 NOKIA5110_Clear();
        	NOKIA5110_GotoXY(0,0);
        NOKIA5110_Puts("The warning have been setup");
NOKIA5110_GotoXY(0,1);
	NOKIA5110_Puts("warning");
	if(warning==0) {NOKIA5110_Puts("on "); } else {NOKIA5110_Puts("off");}
NOKIA5110_GotoXY(0,2);
NOKIA5110_Puts("water");
	if(water==0) {NOKIA5110_Puts("on "); } else {NOKIA5110_Puts("off");}

	
}
void interface_warning_on(void)
{
	   NOKIA5110_GotoXY(0,1);
	NOKIA5110_Puts("warning");
	if(warning==0) {NOKIA5110_Puts("on "); warning=1; } else {NOKIA5110_Puts("off"); warning=0;}
	
}
void interface_warning_off(void)
{NOKIA5110_GotoXY(0,1);
	NOKIA5110_Puts("warning");
	if(warning==0) {NOKIA5110_Puts("on "); warning=1; } else {NOKIA5110_Puts("off"); warning=0;}
	
	
}

void interface_wate_on(void){
NOKIA5110_GotoXY(0,2);
NOKIA5110_Puts("water");
	if(water==0) {NOKIA5110_Puts("on "); water=1; } else {NOKIA5110_Puts("off"); water=0;}
}
void interface_wate_off(void){
NOKIA5110_GotoXY(0,2);
NOKIA5110_Puts("water");
	if(water==0) {NOKIA5110_Puts("on "); water=1; } else {NOKIA5110_Puts("off"); water=0;}

}



