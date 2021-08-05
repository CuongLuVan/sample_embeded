
  #include "stm32f4xx.h"
  #include "stm32f4xx_rtc.h"
#include "lcd_320x240.h"

char show_hexa[320];

char hienthi_hex(char a){

if(a==0x00) return '0';
if(a==0x01) return '1';
if(a==0x02) return '2';
if(a==0x03) return '3';	
if(a==0x04) return '4';	
if(a==0x05) return '5';
if(a==0x06) return '6';
if(a==0x07) return '7';
if(a==0x08) return '8';
if(a==0x09) return '9';
if(a==0x0a) return 'a';
if(a==0x0b) return 'b';
if(a==0x0c) return 'c';
if(a==0x0d) return 'd';
if(a==0x0e) return 'e';
if(a==0x0f) return 'f';	
return 'x';
} 


void display_text(int dodai,char* kytu){
int t,k;
char	m,o;
k=dodai*3;

for(t=0;t<k;t++){
o=*kytu;
m=o/16;	
show_hexa[t]=hienthi_hex(m);	
m=o%16;	
t++;	
show_hexa[t]=hienthi_hex(m);	
t++;
show_hexa[t]=',';	
*kytu++;
}	

display_tex_theododai(0,k,show_hexa);
}