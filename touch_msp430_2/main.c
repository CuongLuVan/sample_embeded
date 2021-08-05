/* --COPYRIGHT--,BSD_EX
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *******************************************************************************
 *
 *                       MSP430 CODE EXAMPLE DISCLAIMER
 *
 * MSP430 code examples are self-contained low-level programs that typically
 * demonstrate a single peripheral function or device feature in a highly
 * concise manner. For this the code may rely on the device's power-on default
 * register values and settings such as the clock configuration and care must
 * be taken when combining code from several examples to avoid potential side
 * effects. Also see www.ti.com/grace for a GUI- and www.ti.com/msp430ware
 * for an API functional library-approach to peripheral configuration.
 *
 * --/COPYRIGHT--*/
//******************************************************************************
//  MSP430G2xx3 Demo - 4-button Capacitive Touch, Pin Oscillator Method, ACLK CCR
//
//  Description: Basic 4-button input using the built-in pin oscillation feature
//  on GPIO input structure. PinOsc signal feed into TA0CLK. ACLK [32kHz] is fed
//  into the CCR1 register, triggering the CCR flag in timer capture mode.
//  Difference in measurements indicate button touch. LEDs flash according to the
//  input touched:
//
//  Input 1: LED1 (LED2 off)
//  Input 2: LED2 (LED1 off)
//  Input 3: Both LEDs on
//  Input 4: Both LEDs flash on/off
//
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = 1MHz DCO
//
//               MSP430G2xx3
//             -----------------
//         /|\|              XIN|-
//          | |                 |  32kHz xtal
//          --|RST          XOUT|-
//            |                 |
//            |             P2.0|<--Capacitive Touch Input 1
//            |                 |
//  LED 2  <--|P1.6         P2.1|<--Capacitive Touch Input 2
//            |                 |
//  LED 1  <--|P1.0         P2.2|<--Capacitive Touch Input 3
//            |                 |
//            |             P2.3|<--Capacitive Touch Input 4
//
//   Brandon Elliott/D. Dang
//  Texas Instruments Inc.
//  November 2010
//   Built with IAR Embedded Workbench Version: 5.10
//******************************************************************************


#include <msp430g2253.h>
#include "lcd.h"
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
char key_pressed;
int cycles;
const unsigned char electrode_bit[NUM_SEN]={BIT0, BIT1, BIT2, BIT3};
/* System Routines*/

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



void dieukhienthietbi(unsigned char a){
	P2DIR |=  contr1;        //
	P2DIR |=  contr2;
	P2DIR |=  contr3;
	P2DIR |=  contr4;

	if((a&0x01)==0) P2OUT |=  contr1; else P2OUT &=  ~contr1;
	if((a&0x02)==0) P2OUT |=  contr2; else P2OUT &=  ~contr2;
	if((a&0x04)==0) P2OUT |=  contr3; else P2OUT &=  ~contr3;
	if((a&0x08)==0) P2OUT |=  contr4; else P2OUT &=  ~contr4;


}
/* Main Function*/
int main(void)
{
	 unsigned int i,j;
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


	   __bis_SR_register(GIE);
 khoitao();

key_press=0;
key_pressed=0;
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

  }
}                                           // End Main

/* Measure count result (capacitance) of each sensor*/
/* Routine setup for four sensors, not dependent on NUM_SEN value!*/









/* Timer A1 interrupt service routine*/
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0 (void)
{
   __bic_SR_register_on_exit(LPM3_bits);     // Exit LPM3 on reti
}


