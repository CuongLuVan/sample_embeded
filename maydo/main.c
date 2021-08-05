#include <msp430.h> 
#include <C:\Documents and Settings\home\My Documents\workspace\maydo\lcd.h>
unsigned int thoi1,coub;
unsigned int susa;



unsigned long mang,thoi,dulieu[150];

unsigned char save,save_w;


void docgiatri1(unsigned int t){
char i;

i=t/10000;
t=t%10000;
i=i+'0';
ghikt(i);
i=t/1000;
t=t%1000;
i=i+'0';
ghikt(i);
i=t/100;
t=t%100;
i=i+'0';
ghikt(i);
i=t/10;
t=t%10;
i=i+'0';
ghikt(i);
i=t;
i=i+'0';
ghikt(i);
}

void docgiatri2(unsigned char t){
char i;
i=t/100;
t=t%100;
i=i+'0';
ghikt(i);
i=t/10;
t=t%10;
i=i+'0';
ghikt(i);
i=t;
i=i+'0';
ghikt(i);
}




void docgiatri(unsigned long t){
char i;
unsigned long p;

lcd_puts("do");
i=t/1000000000;
p=t%1000000000;
i=i+'0';
ghikt(i);
i=p/100000000;
p=p%100000000;
i=i+'0';
ghikt(i);
i=p/10000000;
p=p%10000000;
i=i+'0';
ghikt(i);
i=p/1000000;
p=p%1000000;
i=i+'0';
ghikt(i);
i=p/100000;
p=p%100000;
i=i+'0';
ghikt(i);
i=p/10000;
p=p%10000;
i=i+'0';
ghikt(i);
i=p/1000;
p=p%1000;
i=i+'0';
ghikt(i);
i=p/100;
p=p%100;
i=i+'0';
ghikt(i);
i=p/10;
p=p%10;
i=i+'0';
ghikt(i);
i=p;
i=i+'0';
ghikt(i);
}


void nut_bam(void){
unsigned int yu,d1,d2; 
unsigned long lu;
yu=0;
d1=0;
d2=0;

      for(susa=0;susa<150;susa++){
      	lu=dulieu[susa];
      	lu=lu%100000;
      if (lu>2000) {
      lu=dulieu[susa];
      	yu=lu/100000;
      	if((yu==1)&&(d1==0)) {
      		lu=lu%100000;
      	if (lu<10000) d1=lu/200;
      	}
      	      	if((yu==2)&&(d2==0)) {
      		lu=lu%100000;
      	if (lu<10000) d2=lu/200;
      	}
      	      	      	if((yu==3)) {
      		lu=lu%100000;
      	if ((lu<10000)&&(d2==0)) d2=lu/200;
      	 	if ((lu<10000)&&(d1==0)) d1=lu/200;
      	}
      	  
           }
      
      
      }
      d1=d1*100+d2;

               lcd_clear();
              lcd_puts("vitri");
               ghilenh(0xc0);
              docgiatri1(d1);
              _delay_cycles(40000000);



}



void main(void){
unsigned int nut;
unsigned char chu;

WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

 //UCSCTL6 &= ~(XT2OFF);                     // XT1 On
 // UCSCTL6 |= XCAP_3;
// UCSCTL6 &= 0x3fff;
 // UCSCTL6 |= 0x4000;
 //UCSCTL6=XT1OFF+XT2DRIVE0;
// UCSCTL4=SELS__XT2CLK ;


UCSCTL3 |= SELREF_2;                // Set DCO FLL reference = REFO
	UCSCTL4 |= SELA_2;                  // Set ACLK = REFO
	P7SEL |= BIT2+BIT3;                       // Port select XT2
		while(BAKCTL & LOCKIO)                    // Unlock XT1 pins for operation
			BAKCTL &= ~(LOCKIO);

		UCSCTL6 &= ~XT2OFF;                       // Enable XT2
		UCSCTL3 |= SELREF_2;                      // FLLref = REFO
		UCSCTL4 |= SELA_2;                        // ACLK=REFO,SMCLK=DCO,MCLK=DCO
		// Loop until XT1,XT2 & DCO stabilizes - in this case loop until XT2 settles
	  do
	  {
	    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
	                                            // Clear XT2,XT1,DCO fault flags
	    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
	  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag

	  UCSCTL6 &= ~XT2DRIVE1;                    // Decrease XT2 Drive according to
	                                            // expected frequency
	  UCSCTL4 |= SELS_5 + SELM_5;               // SMCLK=MCLK=XT2                               // Loop in place



  P2DIR = 0xff;                            // P1.0 output
 TA0CCTL0 = CCIE;        // CCR0 interrupt enabled
  TA0CCR0 = 50000;
 TA0CTL = TASSEL_2 + MC_1 + TACLR;        // SMCLK, contmode, clear TAR
 // TA0CTL=TAIE;
  
  
 __bis_SR_register(GIE);       // Enter LPM0, enable interrupts

khoitao();
lcd_clear();

lcd_puts("hehhehe");
P2OUT=0xf0;

  P4DIR = 0;   
  P4OUT=0xff;
  
  while(1){
  	
  	
  	
  	//for(nut=0;nut<500;nut++) vao[nut]=0;
  	   TA0CCR0=237;
  	      lcd_clear();
  	   
          lcd_puts("do cong huong");
          _delay_cycles(120);  
           
     //    for(nut=395;nut<405;nut++) 
     nut=400;
     {
       	 for(susa=0;susa<100;susa++) dulieu[susa]=0;
  	       lcd_clear();
           lcd_puts("tanso");
           chu=nut/10;
           docgiatri2(chu);
           ghikt('.');
           chu=nut%10+'0';
           ghikt(chu);
          _delay_cycles(120000);  
          
            //    lcd_puts("tim");
  	       /// _delay_cycles(20000);
  	      
  	           ghilenh(0xc0);
  	         thoi1=0; 
  	        TA0CCR0=237;
  	            while(thoi1<3);
  	            
            TA0CCR0 = 60000/nut;
            save=60000/nut;
            while(thoi1<20);
            TA0CCR0=237;
            thoi1=0; 
            susa=0;
            chu=0;
            
           while((thoi1<150)){
           	save_w=P4IN&0x03;
                 if(save_w!=chu){ dulieu[susa]=thoi1*save+TA0R+save_w*100000;
                                                susa++;   chu=save_w; }
            
                   
                 if( susa==150)  susa=149;
                   	        //       lcd_puts("=>xac lap");
                   	  	   //    _delay_cycles(60000000);  
                           //    _delay_cycles(60000000);
                           //     goto thoatnan;} 
                          
           }
//thoatnan:
     // susa++;     

     nut_bam();
            
       }
       
       

	
  
  }
  
 

}

// Timer1 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{
	 P2OUT=~P2OUT;
	//unsigned long susa;
	thoi1++;    
	//lcd_clear();
	// susa=thoi1*50;
//	docgiatri(susa);                  // Toggle P1.0
 // TA1CCR0 += 50000;                         // Add Offset to CCR0
}

