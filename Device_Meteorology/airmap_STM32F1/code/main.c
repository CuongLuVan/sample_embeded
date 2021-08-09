/*
file:  main.c
Create date : 19/2/2017
user cread : Lu Van Cuong
*/
#include "stm32f10x.h"
#include "debug.h"
#include "stm32f10x_it.h"
#include "control.h"
#include "define.h"

/******************************************************************************
function:  main
argunent: void
return : int
description : main program
Create date : 19/2/2017
user cread : Lu Van Cuong
******************************************************************************/
int main(void)
{

	uint8_t error_code=0;
	uint32_t counter,newcounter;

	
	USART_Debug_Init(SPEED_BAURATE);
	for(counter=0;counter<34000000;counter++);
  printDebug("START:~~~~~~~main");
  setupAllCompoment();
  printDebug("START:~~~~~~~main1");

  if (SysTick_Config(SystemCoreClock / 1000))
  { 
		printDebug("START:Error system tick");
    /* Capture error */ 
    while (1);
  }
	printDebug("START:~~~~~~~main2");
	  counter =getSysTick();
	 while (1)
  {
		newcounter=getSysTick()/100;
		if(counter!=newcounter){
			counter=newcounter;
			error_code=getAllDataSensor();
		}
		if(error_code){
			sendUARTData();
		}
	}
 // printDebug("End:main");
}

void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}

