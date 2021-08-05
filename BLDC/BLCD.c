//*****************************************************/
//*****************************************************/
//*****************************************************/
///////////////////////////////////////////////////////
/*
chuong trinh dieu khien dong co khong choi than (BLDC)
chip su dung: AT89S52
*/

#include <REGX51.H>

#define set 1
#define clr 0
#define on 0
#define off 1

sfr P00=0x80;
sfr P01=0x90;
sfr P02=0xa0;

///////////////////////////////////////////////////////
//ban phim
sbit add=P3^2;// interrupt0
sbit sub=P3^3;// interrupt1
sbit finish=P3^6;
sbit setup=P3^7;

///////////////////////////////////////////////////////
//LCD 16x2
//giao tiep 8 bits
//cong du lieu P00
sbit rs=P2^7;
sbit rw=P2^6;
sbit e=P2^5;

///////////////////////////////////////////////////////
//chan dieu khien song co
sbit l0=P1^0;
sbit l1=P1^1;
sbit l2=P1^2;
sbit l3=P1^3;
sbit l4=P1^4;
sbit l5=P1^5;

///////////////////////////////////////////////////////

//****************************************************/
//cac bien toan cuc
int n;
int count=0;
int present;//toc do hien tai
unsigned int sub_speed;//dieu khien toc do
bit sub_present=0;//chieu dong co thuan
bit setup_status=0;//chua vao trang thai setup
bit finish_status=0;//chua vao trang thai finish
//int sub_speed;//bien phu o trong ngat

//////////////////////////////////0///////////////////									  14  15					 21	  22				  27  28								  37  38				  43  44				  49	  	  
unsigned char display_array[50]={'D','i','e','u',' ','k','h','i','e','n',' ','B','L','D','C','C','a','i',' ','d','a','t','T','o','c',' ','d','o','C','h','i','e','u',' ','q','u','a','y',' ','t','h','u','a','n',' ','n','g','u','o','c'};
unsigned char speed_array[10]={'0','1','2','3','4','5','6','7','8','9'};
//****************************************************/
/*
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
*/

void speed_add (void)   interrupt 0//ngat ngoai 0
{
   present=200;
} 

void timer0 (void)   interrupt 1
{
 count++;
 TF0=clr;
}

void speed_sub (void)   interrupt 2//ngat ngoai 1
{
   present=200;
}



//cac chuong tinh con
//*****************************************************/
void delay(long time)
{
 long m;
 for(m=0;m<time;m++)
 {
  ;
 }
}
///////////////////////////////////////////////////////

//*****************************************************/
void LCD_data(void)
{
 delay(10);
 rs=set;
 delay(10);
 rw=clr;
 delay(10);
 e=set;
 delay(10);
 e=clr;
 delay(10);
 } 
////////////////////////////////////////////////////////

//*****************************************************/
void LCD_command(void)
{
 delay(10);
 rs=clr;
 delay(10);
 rw=clr;
 delay(10);
 e=set;
 delay(10);
 e=clr; 
 delay(10);
}
///////////////////////////////////////////////////////

///*****************************************************/
void LCD_init(void)
{
 //data=0x06;
 //_delay_ms(1000);
 //LCD_command();

 P00=0x38;//function set
 delay(200);
 LCD_command();
 //_delay_ms(100);
 P00=0x0c;//control set
 delay(200);
 LCD_command();
 //_delay_ms(1000);

 P00=0x01;//clr
 delay(200);
 LCD_command();
}
///////////////////////////////////////////////////////

//*****************************************************/
void display_arr(int start ,int end)
{	   
	int i;
	for(i=start; i<=end; i++)
	{
		 P00=display_array[i];
		 LCD_data();
	}
}
///////////////////////////////////////////////////////

//*****************************************************/
void forward(void)
{
    P01=17;//phase 12
    delay(present); 
    P01=20;//phase 11
    delay(present);
    P01=12;//phase 10
    delay(present);
    P01=10;//phase 9
    delay(present);
    P01=34;//phase 8
    delay(present);
    P01=33;//phase 7
    delay(present);
    P01=17;//phase 6
    delay(present);
    P01=20;//phase 5
    delay(present);
    P01=12;//phase 4
    delay(present);
    P01=10;//phase 3
    delay(present);
    P01=34;//phase 2
    delay(present);
    P01=33;//phase 1
    delay(present);
}
///////////////////////////////////////////////////////

//*****************************************************/
void back(void)
{
    P01=33;//phase 1
    delay(present); 
    P01=34;//phase 2
    delay(present);
    P01=10;//phase 3
    delay(present);
    P01=12;//phase 4
    delay(present);
    P01=20;//phase 5
    delay(present);
    P01=17;//phase 6
    delay(present);
    P01=33;//phase 7
    delay(present);
    P01=34;//phase 8
    delay(present);
    P01=10;//phase 9
    delay(present);
    P01=12;//phase 10
    delay(present);
    P01=20;//phase 11
    delay(present);
    P01=17;//phase 12
    delay(present); 	
}
///////////////////////////////////////////////////////

//*****************************************************/
void sub_speed_calculator(void)
{
	unsigned int sub_cycle;//vong tren phut
	sub_cycle=150000/((2*sub_speed)-5);//chua so vong tren phut
	P00=' ';
	LCD_data();
	
	P00=speed_array[sub_cycle/1000];//hang nghin
	LCD_data();
	sub_cycle=sub_cycle%1000;//lay 3 so
	
	P00=speed_array[sub_cycle/100];//hang tram
	LCD_data();

	sub_cycle=sub_cycle%100;//lay 2 so
	
	P00=speed_array[sub_cycle/10];//hang chuc
	LCD_data();
	
	P00=speed_array[sub_cycle%10];//hang don vi
	LCD_data();
	P00=' ';
	LCD_data();
	P00='V';
	LCD_data();
	P00='/';
	LCD_data();
	P00='P';
	LCD_data();
}
///////////////////////////////////////////////////////

//*****************************************************/
void speed_calculator(void)
{
    int sub_cal;
	P00=' ';
	LCD_data();
	P00=speed_array[present/100];//hang tram
	LCD_data();
	sub_cal=present%100;
	P00=speed_array[sub_cal/10];//hang chuc
	LCD_data();
	P00=speed_array[sub_cal%10];//hang don vi
	LCD_data();
}
///////////////////////////////////////////////////////







///*****************************************************/











//*****************************************************/
//void (void)
//{

//}
///////////////////////////////////////////////////////






////////////////////////////
void main(void)
{
add=set;
sub=set;
finish=set;
setup=set;
P01=0;
delay(50000);
ET0=set;//cho phep ngat timer0
TMOD=0x02;//8 bit tu nap lai(timer0)
TH0=0x00;//
TL0=0x00;
//ET0=set;//cho phep ngat timer0

EX0=set;//enable ex_interrupt 0
T0=clr;//enable edge interrupt
EX1=set;
T1=clr;	 
 
EA=set; //enable all source
LCD_init();

sub_speed=200;//gia tri khoi tao
present=200;
P00=0x01;//clr
delay(100);
LCD_command();

display_arr(0, 14);//hien khoi tao
delay(50000);
P00=0x01;//clr
delay(100);
LCD_command();
display_arr(22, 27);//hien toc do
//speed_calculator();//tinh toan va hien thi vong quay
//P00='-';//hien mui ten
//LCD_data();
//P00='>';//hien mui ten
//LCD_data();
sub_speed_calculator();//hien thi vong 
P00=0xc0;//ve dau dong 2
delay(100);
LCD_command();

display_arr(28, 37);//hien chieu
display_arr(38, 43);//hien thuan
delay(20000);
TR0=clr;
TF0=clr;
TR0=set;//khoi dong timer0
//IE=0x82;//
while(1)
{
     if(setup==0)//vao trang thai setup
       {
	   present=200;
	   while(finish==1)//khi chua ket thuc
	   {
	        //setup_status=1;
	        P01=0;//tat dong co
			//EA=clr; //disable all source
			EX0=clr;
			EX1=clr;
			count=0;
	        P00=0x80;//ve dau dong 1
            delay(5);
            LCD_command();
	        display_arr(22, 27);//hien toc do
			if(add==0&&sub_speed<246)
			{
			  sub_speed=sub_speed+5;
			}
			if(sub==0&&sub_speed>41)
			{
			  sub_speed=sub_speed-5;
			}

	        sub_speed_calculator();//tinh toan va hien thi vong quay
			//P00='-';//hien mui ten
            //LCD_data();
            //P00='>';//hien mui ten
            //LCD_data();
	        //sub_speed_calculator();//hien thi vong ke tiep
	        P00=0xc0;//ve dau dong 2
            delay(5);
            LCD_command();
			if(setup==0)//cai dat chieu quay
			{
			  delay(100);
			  if(setup==0)
			  {
			    delay(300);
			    sub_present=!sub_present;//bien chieu quay
			  }
			}
	        display_arr(28, 37);//hien chieu quay
	        if(sub_present==0)//kiem tra chieu quay
	        {
		      display_arr(38, 43);//hien thuan
	        }
	        else
	        {
		        display_arr(44, 49);//hien nguoc
	        }
	    }
     }

     //if(finish==0)//hoan tat cong viec
     //{
	   //setup_status=0;//binh thuong
	   //finish_status=0;//binh thuong
	   //present=sub_speed;//gan toc do moi  
	   //if(finish_status==1)
	   //{
	     
		 //hien thi dong dau tien (toc do 350->350)
	   //}

     //}
	 
      
	  EX0=set;
	  EX1=set;
	  while(TF0==0)//cho co TF0
	  {
	  	   EX0=set;
	  }
      if(sub_present==0)
	  {
		if(present<=sub_speed&&count>800)//kiem tra da thay doi o phim finish chua de hien len LCD
		{
		  present=present+1;
		  count=0;
		}
		if(present>sub_speed&&count>800)
		{
		  present=present-1;
		  count=0;
		} 
		forward();//quay thuan
	  }
	  else
	  {
		  if(present<=sub_speed&&count>800)//kiem tra da thay doi o phim finish chua de hien len LCD
		  {
		    present=present+1;
			count=0;
		  }
		  if(present>sub_speed&&count>800)
		  {
		    present=present-1;
			count=0;
		  }
		  //if()//kiem tra da thay doi o phim finish chua de hien len LCD
		  back();//quay nguoc
	  }
      //if(finish==0)
      //{
  	    //sub_present=0;
      //}
	 
}

}