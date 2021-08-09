
#include "stm32f10x.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
#include "lcd_320x240.h"
uint8_t  mang_dothi[600],apmau[8];
uint16_t valueADC;	
uint32_t	bodemxav;
uint32_t	bodemxaz;
uint32_t	bodemxak;
#define ADC1_DR_Address    ((uint32_t)0x4001244C)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
ADC_InitTypeDef ADC_InitStructure;
DMA_InitTypeDef DMA_InitStructure;
__IO uint16_t ADCConvertedValue;

				double Q_angle = 0.005; //0.001    //0.005
        double Q_gyro = 0.003;  //0.003  //0.0003
        double R_angle = 0.03;  //0.03     //0.008

        double x_bias = 0;
        double P_00 = 0, P_01 = 0, P_10 = 0, P_11 = 0;
        double y, S;
        double K_0, K_1;
        double x_angle;


  double kalmanCalculate(double newAngle, double newRate, double looptime)
        {

            double dt = (looptime) / 1000;                                    // XXXXXXX arevoir
            x_angle += dt * (newRate - x_bias);
            P_00 += -dt * (P_10 + P_01) + Q_angle * dt;
            P_01 += -dt * P_11;
            P_10 += -dt * P_11;
            P_11 += +Q_gyro * dt;
            //x=A*x(k-1)+Bu
            // P=AP(k-1)At+Q
            //Kk=P*Ht*(H*P*Ht+R)-1
            //xm=x+Kk(zk-H*x)
            //Pm=(I-Kk*H)*P
            y = newAngle - x_angle;
            S = P_00 + R_angle;
            K_0 = P_00 / S;
            K_1 = P_10 / S;

            x_angle += K_0 * y;
            x_bias += K_1 * y;
            P_00 -= K_0 * P_00;
            P_01 -= K_0 * P_01;
            P_10 -= K_1 * P_00;
            P_11 -= K_1 * P_01;

            return x_angle;
        }
void setup_dma_adc(){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_ADCCLKConfig(RCC_PCLK2_Div4); 
  /* Enable peripheral clocks ------------------------------------------------*/
  /* Enable DMA1 clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

  /* Enable ADC1 and GPIOC clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);
  /* Configure PC.04 (ADC Channel14) as analog input -------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
/* DMA1 channel1 configuration ----------------------------------------------*/
  DMA_DeInit(DMA1_Channel3);
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedValue;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 1;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  
  /* Enable DMA1 channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);
  
  /* ADC1 configuration ------------------------------------------------------*/
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channel14 configuration */ 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime_55Cycles5);

  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* Enable ADC1 reset calibration register */   
  ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));

  /* Start ADC1 calibration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));     
  /* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);

}

void RCC_Configuration(void)
{
  /* PCLK1 = HCLK/4 */
  RCC_PCLK1Config(RCC_HCLK_Div2);
  /* GPIOC clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
}

void GPIO_Configuration(void)
{     	GPIO_InitTypeDef GPIO_InitStructure;
GPIO_InitTypeDef kieu;

	  
		SystemCoreClockUpdate ();
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
    RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |RCC_APB2Periph_GPIOE, ENABLE);
    kieu.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
	  kieu.GPIO_Speed=GPIO_Speed_50MHz;
	  kieu.GPIO_Mode=GPIO_Mode_Out_PP;
        GPIO_Init(GPIOA,&kieu);
	  kieu.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	  kieu.GPIO_Speed=GPIO_Speed_50MHz;
	  kieu.GPIO_Mode=GPIO_Mode_Out_PP;
        GPIO_Init(GPIOB,&kieu);
  	kieu.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
	  kieu.GPIO_Speed=GPIO_Speed_50MHz;
	  kieu.GPIO_Mode= GPIO_Mode_Out_PP;;
        GPIO_Init(GPIOA,&kieu);
	
}




void xacdinhtanso(void){
uint8_t bieumau,min,max;
char	a[3];
uint16_t dem,begin_s,loadx,loady,dotim;	
uint32_t congdon;

	  begin_s=bodemxav/100;	
		max=0;
	  min=0;
	  loadx=begin_s;
	if((loadx<199)&&(loadx>110)){
					for(dem=begin_s;dem>begin_s-40;dem--) {
												if((mang_dothi[dem]>mang_dothi[dem-1])&&(mang_dothi[dem]>mang_dothi[dem+1])){
																									loadx=dem;   break;
																							}
																					}

					for(dem=loadx-26;dem>loadx-40;dem--) {
												if((mang_dothi[dem]>mang_dothi[dem-1])&&(mang_dothi[dem]>mang_dothi[dem+1])){
																									loady=dem;   break;
																							}
		}
dem=loadx-loady;
min=2400/dem;
a[0]=min/10+48;
a[1]=min%10+48;
a[2]='\0';		
print1(a,300,220,0);			
	}
	bieumau=0;
if(begin_s==299){
	for(dem=0;dem<300;dem++){
       if((mang_dothi[dem]>mang_dothi[dem-1])&&(mang_dothi[dem]>mang_dothi[dem+1])){
																									bieumau++; dem+=26;
																							}
   }
	for(dem=1;dem<8;dem++) apmau[dem-1]=apmau[dem]; 
	 apmau[7]=bieumau;
	 bieumau=0;
	for(dem=0;dem<8;dem++) bieumau +=apmau[dem];
	 min=0;
	 for(dem=0;dem<8;dem++) if(apmau[dem]==0) min++;
	 if(min==0){
	 a[0]=bieumau/10+48;
   a[1]=bieumau%10+48; 
  a[2]='\0';		
  print1(a,300,180,0);}
}	
	
}




int main(void)
{int uouo,uoui,giatri;
	double taz;
	SystemInit();
_delay_ms(100);
	RCC_Configuration();    
GPIO_Configuration(); 
setup_dma_adc();
	_delay_ms(100);
	sbi(PORT_RD,BIT_RD);
	_delay_ms(100);
	InitLCD(LANDSCAPE);
	_delay_ms(100);
	fillScr2(VGA_WHITE);
		_delay_ms(100);
	setBackColor2(VGA_WHITE); 
//	mx_sd_config();
	_delay_ms(100);
	setColor2(VGA_BLUE);	

print1("xin chao",10,10,0);
 // while (1)
  {
			_delay_ms(100);	
if(SysTick_Config(SystemCoreClock /4000))
  { 
print1("co loi xay ra",0,0,0);
    /* Capture error */ 
    while (1);
  }
//fillScr2(VGA_RED);
	giatri=0;
drawLine(20, 20, 20,320);	
drawLine(20, 20, 240,20);		
print1("0 ",0,0,0);
print1("1 ",70,0,0);
print1("2 ",120,0,0);
print1("3 ",170,0,0);
print1("4 ",220,0,0);
print1("5 ",270,0,0);	
print1("1 ",0,70,0);
//print1("2 ",0,120,0,0);
print1("3 ",0,170,0);
//print1("4 ",0,220,0,0);	

//	drawfige(&mang_dothi[0]);	
		_delay_ms(10);	
//drawfige_e(&mang_dothi[0]);
giatri=0;
	bodemxav=0;
		bodemxak=0;
	for(giatri=0;giatri<300;giatri++)mang_dothi[giatri]=0;
			giatri=0;	
  }
while(1){
	 xacdinhtanso();
  giatri=bodemxav/100;
	//mang_dothi[giatri]=GetData(ACCEL_XOUT_H)/300;if
	if(bodemxaz!=0) {
if(giatri!=0){
taz=kalmanCalculate(mang_dothi[giatri] * 1.0, mang_dothi[giatri]-mang_dothi[giatri-1],(bodemxak/100)*0.09);
mang_dothi[giatri]=(uint8_t) taz;
}
 bodemxaz=0;}

if(((giatri%10)==0)&&(bodemxaz==0)&&(giatri<291))	
	drawfige(&mang_dothi[0]);	
			if(giatri>298) {drawfige_e(&mang_dothi[0]);
 for(giatri=0;giatri<300;giatri++)mang_dothi[giatri]=0;
			giatri=0;	
  } 
	
	//while((bodemxav%10)==0);
	//if(bodemxav>599){ 
//for(giatri=0;giatri<600;giatri++)mang_dothi[giatri]=0;
//giatri=0; bodemxav=0;}

}
		
}









void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}




