/**
  @page USART_DataExchangeDMA USART Communication Boards Data Exchange using DMA example
  
  @verbatim
  ******************** (C) COPYRIGHT 2013 STMicroelectronics *******************
  * @file    USART/USART_TwoBoards/USART_DataExchangeDMA/readme.txt 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    04-August-2014
  * @brief   Description of the USART Communication Boards Data Exchange using 
  *          DMA example.
  ******************************************************************************
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  @endverbatim

@par Example Description 

This example shows how to use TAMPER button to trigger USART communications 
using DMA and though using USART firmware library.

- Hardware Description

To use this example, you need to load it on two STM32 boards (let's call them 
BoardA and BoardB) then connect these two boards through USART lines and GND.
In the firmware example uncomment the dedicated line in the main.h file to use
the USART peripheral as STM32 Transmitter or as STM32 Receiver device.

@verbatim
*------------------------------------------------------------------------------*
|                BoardA                                  BoardB                |
|         ____________________                   ____________________          |
|        |                    |                 |                    |         |
|        |                    |                 |                    |         | 
|        |     __________     |                 |     __________     |         |
|        |    |   USART  |____|TX_____________RX|____|   USART  |    |         |
|        |    |  Device1 |____|RX_____________TX|____|  Device2 |    |         |
|        |    |____TX____|    |                 |    |____RX____|    |         |
|        |                    |                 |                    |         |
|        |  O LED1            |                 |  O LED1            |         |
|        |  O LED2   TAMPER   |                 |  O LED2   TAMPER   |         |
|        |  O LED3       _    |                 |  O LED3       _    |         |
|        |  O LED4      |_|   |                 |  O LED4      |_|   |         |
|        |                    |                 |                    |         |
|        |             GND O--|-----------------|--O GND             |         |
|        |____________________|                 |____________________|         |
|                                                                              |
|                                                                              |
*------------------------------------------------------------------------------*
@endverbatim



typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

     
   Definition for USARTx resources ******************************************/
	#include "stm32f4xx.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_crc.h"
#include "stm32f4xx_dbgmcu.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_flash.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_iwdg.h"
#include "stm32f4xx_pwr.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_rtc.h"
#include "stm32f4xx_sdio.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_wwdg.h"
	
  #define USARTx                           USART2
  #define USARTx_CLK                       RCC_APB1Periph_USART2
  #define USARTx_CLK_INIT                  RCC_APB1PeriphClockCmd
  #define USARTx_IRQn                      USART2_IRQn
  #define USARTx_IRQHandler                USART2_IRQHandler

  #define USARTx_TX_PIN                    GPIO_Pin_2                
  #define USARTx_TX_GPIO_PORT              GPIOA                       
  #define USARTx_TX_GPIO_CLK               RCC_AHB1Periph_GPIOA
  #define USARTx_TX_SOURCE                 GPIO_PinSource2
  #define USARTx_TX_AF                     GPIO_AF_USART2

  #define USARTx_RX_PIN                    GPIO_Pin_3                
  #define USARTx_RX_GPIO_PORT              GPIOA                    
  #define USARTx_RX_GPIO_CLK               RCC_AHB1Periph_GPIOA
  #define USARTx_RX_SOURCE                 GPIO_PinSource3
  #define USARTx_RX_AF                     GPIO_AF_USART2

  /* Definition for DMAx resources ********************************************/
  #define USARTx_DR_ADDRESS                ((uint32_t)USART2 + 0x04) 

  #define USARTx_DMA                       DMA1
  #define USARTx_DMAx_CLK                  RCC_AHB1Periph_DMA1
     
  #define USARTx_TX_DMA_CHANNEL            DMA_Channel_4
  #define USARTx_TX_DMA_STREAM             DMA1_Stream3
  #define USARTx_TX_DMA_FLAG_FEIF          DMA_FLAG_FEIF3
  #define USARTx_TX_DMA_FLAG_DMEIF         DMA_FLAG_DMEIF3
  #define USARTx_TX_DMA_FLAG_TEIF          DMA_FLAG_TEIF3
  #define USARTx_TX_DMA_FLAG_HTIF          DMA_FLAG_HTIF3
  #define USARTx_TX_DMA_FLAG_TCIF          DMA_FLAG_TCIF3
              
  #define USARTx_RX_DMA_CHANNEL            DMA_Channel_4
  #define USARTx_RX_DMA_STREAM             DMA1_Stream1
  #define USARTx_RX_DMA_FLAG_FEIF          DMA_FLAG_FEIF1
  #define USARTx_RX_DMA_FLAG_DMEIF         DMA_FLAG_DMEIF1
  #define USARTx_RX_DMA_FLAG_TEIF          DMA_FLAG_TEIF1
  #define USARTx_RX_DMA_FLAG_HTIF          DMA_FLAG_HTIF1
  #define USARTx_RX_DMA_FLAG_TCIF          DMA_FLAG_TCIF1

  #define USARTx_DMA_TX_IRQn               DMA1_Stream3_IRQn
  #define USARTx_DMA_RX_IRQn               DMA1_Stream1_IRQn
  #define USARTx_DMA_TX_IRQHandler         DMA1_Stream3_IRQHandler
  #define USARTx_DMA_RX_IRQHandler         DMA1_Stream1_IRQHandler


#define BUFFERSIZE                       100

