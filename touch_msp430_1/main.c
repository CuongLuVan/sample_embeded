

#include <msp430.h>
#define LCD_RS			BIT0
#define LCD_EN			BIT3
#define LCD_D4          BIT4
#define LCD_D5          BIT5
#define LCD_D6          BIT6
#define LCD_D7          BIT7
/* Sensor settings*/
#define NUM_SEN     4                       // Defines number of sensors
#define KEY_LVL     1000                     // Defines threshold for a key press
/*Set to ~ half the max delta expected*/
#define contr1			BIT4       //p2
#define contr2			BIT5
#define contr3          BIT6
#define contr4          BIT7
// Global variables for sensing
unsigned int base_cnt[NUM_SEN];
unsigned int meas_cnt[NUM_SEN];
int delta_cnt[NUM_SEN];
unsigned char key_press;
int cycles;
const unsigned char electrode_bit[NUM_SEN]={BIT1, BIT2, BIT4, BIT5};
/* System Routines*/
void measure_count(void);                   // Measures each capacitive sensor
void dieukhienthietbi(unsigned char a);
void delayLCD();
void ghilenh(unsigned char lenh);
void ghikt(char kt);
void lcd_puts(char *sttt);
void khoitao(void);
void lcd_clear(void);
 char taa;
/* Main Function*/
void main(void)
{
  unsigned int i;
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  if (CALBC1_1MHZ==0xFF)					// If calibration constant erased
  {
    while(1);                               // do not load, trap CPU!!
  }
  DCOCTL = 0;                               // Select lowest DCOx and MODx settings
  BCSCTL1 = CALBC1_1MHZ;                    // Set DCO to 1, 8, 12 or 16MHz
  DCOCTL = CALDCO_1MHZ;
  BCSCTL2 |= DIVS_2;                        // SMCLK/(0:1,1:2,2:4,3:8)
  BCSCTL1 |= DIVA_1;                        // ACLK/(0:1,1:2,2:4,3:8)
  BCSCTL3 |= XCAP_1;                        // Configure Load Caps
  IE1 |= WDTIE;                             // enable WDT interrupt

 do
 {
    IFG1 &= ~OFIFG;                         // Clear OSCFault flag
    for (i = 0xFF; i > 0; i--);             // Time for flag to set
  }
  while (IFG1 & OFIFG);                     // OSCFault flag still set?


   __bis_SR_register(GIE);                  // Enable interrupts

   khoitao();

   key_press=0;
     /* Main loop starts here*/
     while (1)
     {
       measure_count();                        // Measure all sensors
       //bat tat den1
   if(meas_cnt[0]<300){ if((key_press&0x01)==0) key_press|=0x01; else key_press&=0xfe;
   dieukhienthietbi(key_press);
   while (meas_cnt[0]<300) measure_count();
   }
   // battat den2

   if(meas_cnt[1]<300){ if((key_press&0x02)==0) key_press|=0x02; else key_press&=0xfd;
   dieukhienthietbi(key_press);
   while (meas_cnt[1]<300) measure_count();
   }

   // battat den3

   if(meas_cnt[2]<300){ if((key_press&0x04)==0) key_press|=0x04; else key_press&=0xfb;
   dieukhienthietbi(key_press);
   while (meas_cnt[2]<300) measure_count();
   }

   // battat den4

   if(meas_cnt[3]<300){ if((key_press&0x08)==0) key_press|=0x08; else key_press&=0xf7;
   dieukhienthietbi(key_press);
   while (meas_cnt[3]<300) measure_count();
   }


   }                                           // End Main
                               // End Main

/* Measure count result (capacitance) of each sensor*/
/* Routine setup for four sensors, not dependent on NUM_SEN value!*/

void measure_count(void)
{
  unsigned int i, j;
  _DINT();                              // Disable interrupts
  DCOCTL = 0;                               // Select lowest DCOx and MODx settings
  BCSCTL1 = (BCSCTL1 & 0x0CF) + DIVA_3; // ACLK/(0:1,1:2,2:4,3:8)
  for (i = 0; i<NUM_SEN; i++)
  {
    // Configure Ports for relaxation oscillator
    P2DIR &= ~ electrode_bit[i];        //
    P2SEL &= ~ electrode_bit[i];        //
    P2SEL2 |= electrode_bit[i];         // Set target Pin Oscillator
    TA0CTL = TASSEL_3 + MC_2 + TACLR;   // PinOsc Clock source, cont mode
    TA0CCTL0 = CM_1 + CCIS_1 + CAP;     // Capture on Pos Edges, ACLK, Cap, Interrupt
    TA0CCTL0 |= CCIE;                   // Enable Interrupt

    __bis_SR_register(LPM3_bits+GIE);   // Wait for TIMER interrupt
    __bis_SR_register(LPM3_bits+GIE);   // Wait for TIMER interrupt
    meas_cnt[i] = TACCR0;               // Save result
    for (j=0;j<15;j++) {
      __bis_SR_register(LPM3_bits+GIE); // Wait for TIMER interrupt
    }
    TA0CTL &= MC_2;                     // Halt Timer
    TA0CCTL0 &= ~CCIE;                  // Disable Interrupt
    meas_cnt[i] = TACCR0 - meas_cnt[i]; // Save Measured
    P2SEL2 &= ~electrode_bit[i];        // Clear target Pin Oscillator
  }
  DCOCTL = 0;                               // Select lowest DCOx and MODx settings
  BCSCTL1 = (BCSCTL1 & 0x0CF) + DIVA_0; // ACLK/(0:1,1:2,2:4,3:8)
}
}
void dieukhienthietbi(unsigned char a){
	P2DIR |=  contr1;        //
	P2DIR |=  contr2;
	P2DIR |=  contr3;
	P2DIR |=  contr4;
	lcd_clear();
	lcd_puts("status A=>D");
	taa=0;
	 ghilenh(0xc0);
	if((a&0x01)==0) { P2OUT |=  contr1; lcd_puts("on  ");} else{ P2OUT &=  ~contr1; lcd_puts("off ");}
	if((a&0x02)==0) {P2OUT |=  contr2; lcd_puts("on  ");} else {P2OUT &=  ~contr2; lcd_puts("off ");}
	if((a&0x04)==0) {P2OUT |=  contr3; lcd_puts("on  ");} else {P2OUT &=  ~contr3; lcd_puts("off ");}
	if((a&0x08)==0) {P2OUT |=  contr4; lcd_puts("on  ");} else {P2OUT &=  ~contr4; lcd_puts("off ");}



}
void delayLCD()
{

    _delay_cycles(2000);
}

//_________________________Ham ghi lenh ra LCD:______________________________________________

void ghilenh(unsigned char lenh)
{   unsigned char tg,full;
	// ghi 4 bit cao
   P3DIR=0xff;
    // P2OUT=8;
    tg=lenh&0xf0;
    full=tg>>4;
    if((full&0x08)==0) P3OUT &=~LCD_D7; else P3OUT|=LCD_D7;
    if((full&0x04)==0) P3OUT &=~LCD_D6; else P3OUT|=LCD_D6;
    if((full&0x02)==0) P3OUT &=~LCD_D5; else P3OUT|=LCD_D5;
    if((full&0x01)==0) P3OUT &=~LCD_D4; else P3OUT|=LCD_D4;
    P3OUT &= ~LCD_RS;
	P3OUT |= LCD_EN;
	//delay_us(3);
	_delay_cycles(3);
	P3OUT &= ~LCD_EN;
      delayLCD();
	//ghi 4 bit thap
    full=lenh&0x0f;
    if((full&0x08)==0) P3OUT &=~LCD_D7; else P3OUT|=LCD_D7;
    if((full&0x04)==0) P3OUT &=~LCD_D6; else P3OUT|=LCD_D6;
    if((full&0x02)==0) P3OUT &=~LCD_D5; else P3OUT|=LCD_D5;
    if((full&0x01)==0) P3OUT &=~LCD_D4; else P3OUT|=LCD_D4;
     P3OUT |= LCD_EN;
    	//delay_us(3);
    	_delay_cycles(3);
    	P3OUT &= ~LCD_EN;
          delayLCD();

}
//__________________________ham ghi ki tu ra LCD:_____________________________________________

void ghikt(char lenh)
{   unsigned char tg,full;
P3DIR=0xff;
   // P2OUT=8;
   tg=lenh&0xf0;
   full=tg>>4;
   if((full&0x08)==0) P3OUT &=~LCD_D7; else P3OUT|=LCD_D7;
   if((full&0x04)==0) P3OUT &=~LCD_D6; else P3OUT|=LCD_D6;
   if((full&0x02)==0) P3OUT &=~LCD_D5; else P3OUT|=LCD_D5;
   if((full&0x01)==0) P3OUT &=~LCD_D4; else P3OUT|=LCD_D4;
   P3OUT |= LCD_RS;
	P3OUT |= LCD_EN;
	//delay_us(3);
	_delay_cycles(3);
	P3OUT &= ~LCD_EN;
     delayLCD();
	//ghi 4 bit thap
   full=lenh&0x0f;
   if((full&0x08)==0) P3OUT &=~LCD_D7; else P3OUT|=LCD_D7;
   if((full&0x04)==0) P3OUT &=~LCD_D6; else P3OUT|=LCD_D6;
   if((full&0x02)==0) P3OUT &=~LCD_D5; else P3OUT|=LCD_D5;
   if((full&0x01)==0) P3OUT &=~LCD_D4; else P3OUT|=LCD_D4;
    P3OUT |= LCD_EN;
   	//delay_us(3);
   	_delay_cycles(3);
   	P3OUT &= ~LCD_EN;
         delayLCD();
}
//_________________________Ham hien thi 1 xau ra lcd:___________________________________________
void lcd_puts(char *sttt)
{
   taa=0;
   while(*sttt) {taa++;
   	if (taa==17) ghilenh(0xc0);

    ghikt(*sttt);
    *sttt++;
    }
}
//__________________________Ham khoi tao LCD:____________________________________________________
void khoitao(void)
{
	taa=0;
    ghilenh(0x03);
    ghilenh(0x03);
    ghilenh(0x03);
    ghilenh(0x32);
    ghilenh(0x28);    //  4-bit, 2 hang, ma tran 5x7
    ghilenh(0x0C);    // bat hien thi, tat con tro
    ghilenh(0x06);    // dich con tro sang phai
    ghilenh(0x01);    // xoa man hinh
}
void lcd_clear(void){
ghilenh(0x01);
taa=0;}



/* Timer A1 interrupt service routine*/
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0 (void)
{
   __bic_SR_register_on_exit(LPM3_bits);     // Exit LPM3 on reti
}
