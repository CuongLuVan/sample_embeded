if(SysTick_Config(SystemCoreClock /4000))
  { 
print1("co loi xay ra",0,0,0);
    /* Capture error */ 
    while (1);
  }
	
	
for(giatri=0;giatri<100;giatri++) {  giatridocvao[0]=GetData(ACCEL_XOUT_H);
					giatridocvao[1]=GetData(ACCEL_YOUT_H);
					giatridocvao[2]=GetData(ACCEL_ZOUT_H);
					giatridocvao[3]=GetData(GYRO_XOUT_H);
					giatridocvao[4]=GetData(GYRO_YOUT_H);
					giatridocvao[5]=GetData(GYRO_ZOUT_H);
Display_Value(giatridocvao[0]/180,20,10);
	Display_Value(giatridocvao[1]/180,20,30);
	Display_Value(giatridocvao[2]/180,20,50);
	Display_Value(giatridocvao[3],20,70);
	Display_Value(giatridocvao[4],20,90);
Display_Value(giatridocvao[5],20,110);
	_delay_ms(30);	
         }	
bodemxav=0;
giatri=0;
while(1){
if(bodemxav<4000) {
	        giatridocvao[0]=GetData(ACCEL_XOUT_H);
					giatridocvao[1]=GetData(ACCEL_YOUT_H);
					giatridocvao[2]=GetData(ACCEL_ZOUT_H);
					giatridocvao[3]=GetData(GYRO_XOUT_H);
					giatridocvao[4]=GetData(GYRO_YOUT_H);
					giatridocvao[5]=GetData(GYRO_ZOUT_H);
	    giatri++;
       } else {
				 	Display_Value(giatri,20,170);
          bodemxav=0;
giatri=0;
      }
}

while(1){
 uart_setup(2);
 uart_setup(3);
if(sosangkytu(&aRxBuffer[0],"grap",4)==1){
	for(giatri=4;giatri<604;giatri++)
	mang_dothi[giatri-4]=	aRxBuffer[giatri];
	drawfige_e(&mang_dothi1[0]);
  drawfige_e(&mang_dothi2[0]);		
  for(giatri=0;giatri<300;giatri++) {
		mang_dothi1[giatri]=mang_dothi[giatri*2];
		mang_dothi2[giatri]=mang_dothi[giatri*2+1];
   }
	 drawfige(&mang_dothi1[0]);	
   drawfige_cx(&mang_dothi2[0]); 
 }
	
}

	
while(1)
	{

		kichban(10);
 giatri=bodemxav/1000;
	 donang=20;
		//	if(xak==1)
				{	xak=0;
					giatridocvao[0]=GetData(ACCEL_XOUT_H);
					giatridocvao[1]=GetData(ACCEL_YOUT_H);
					giatridocvao[2]=GetData(ACCEL_ZOUT_H);
				//	giatridocvao[3]=GetData(GYRO_XOUT_H);
				//	giatridocvao[4]=GetData(GYRO_YOUT_H); 62652
				//	giatridocvao[5]=GetData(GYRO_ZOUT_H);
					
					Display_Value(giatridocvao[0]/18.02,20,170);
					for(giatri=0;giatri<3;giatri++) if((giatridocvao[giatri]/3)>maxp) {maxp = giatridocvao[giatri]/3;   Display_Value(maxp,20,50);  }
				/*	taz=kalmanCalculate(giatridocvao[0] * 1.0,giatridocvao[3]/40000,(bodemxav/40)*0.09);		
					if(taz<65535) 	{ //ox voi mp
						out_print=(int)taz/168.15;
						if(out_print>180) out_print-=360;
						giatridocra[0]=out_print;
					}
					taz=kalmanCalculate2(giatridocvao[1] * 1.0,giatridocvao[4]/40000,(bodemxav/40)*0.09);		
					if(taz<65535) 	{ //oy voi mp
					out_print=(int)taz/168.15;
					if(out_print>180) out_print-=360;
					giatridocra[1]=out_print;
					}
					taz=kalmanCalculate3(giatridocvao[2] * 1.0,giatridocvao[5]/40000,(bodemxav/40)*0.09);		
					if(taz<65535) 	{ //oz voi mp
					out_print=(int)taz/168.15;
					if(out_print>180) out_print-=360;
					giatridocra[2]=out_print;
					}	
          giatri=bodemxav/40;
        mang_dothi[giatri]=(uint8_t)	giatridocvao[0]/256;
        mang_dothi1[giatri]=(uint8_t)	giatridocra[0]/2;	
        					giatri=bodemxav/40;	
				*/

}	

				giatri=bodemxav/40;
	//	if((giatri%300)==0)
			{	
//			drawfige_e(&mang_dothi2[0]);
//drawfige_e(&mang_dothi3[0]);	
	//			drawfige(&mang_dothi[0]);	
		//	drawfige_cx(&mang_dothi1[0]);		
//for(giatri=0;giatri<300;giatri++) {mang_dothi2[giatri]=mang_dothi[giatri];
  //      mang_dothi3[giatri]=mang_dothi1[giatri];  mang_dothi[giatri]=0; mang_dothi1[giatri]=0;}
	/*		giatri=0;				
		Display_Value(CCR1_Val,20,10);	 Display_Value(CCR2_Val,70,10);	Display_Value(CCR3_Val,140,10); Display_Value(CCR4_Val,210,10);					
		Display_Value(gocx,20,30);	         Display_Value(gocy,120,30);			
		Display_Value(maxp,20,50);            Display_Value(donang,120,50);	
				
		Display_Value(giatridocra[0],20,90); 
		Display_Value(giatridocra[1],20,110);
		Display_Value(giatridocra[2],20,130);
				
		Display_Value(giatridocvao[0]/168,20,170);  
		Display_Value(giatridocvao[1]/168,20,190);   
		Display_Value(giatridocvao[2]/168,20,210); 
*/		
}
pwm_setpid(giatridocra[0],giatridocra[1]);
				
}
  }
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
/*
{
		//  uwADCxConvertedVoltage = uhADCxConvertedValue *3300/0xFFF;
		lamlai:
		dem1=0;dem2=0; 
for(bodem=0;bodem<7000;bodem++) {
if((uhADCxConvertedValue[bodem]>50)&&(uhADCxConvertedValue[bodem+1]<50)) dem1=bodem+1;
 }
if(dem1==0) goto lamlai;
		batdau:
   for(bodem=dem1;bodem<12000;bodem++) {
if((uhADCxConvertedValue[bodem]<50)&&(uhADCxConvertedValue[bodem+1]>50)) { dem2=bodem+1; goto hienra;}
 }
goto batdau;
 
 hienra:
 drawfige_e(&dulieuve[0]);
 for(bodem=0;bodem<300;bodem++) {dulieuve[bodem]=0;}
 dorong=dem2-dem1;
 soxunglap=dorong/250;
 xungthap=0;
 xungcao=0;
 if(soxunglap!=0){
for(bodem=dem1;bodem<dem2;bodem++){
if(uhADCxConvertedValue[bodem]<50) xungthap++; else xungcao++;
	dorong=((bodem-dem1)/soxunglap);
dulieuve[dorong]=uhADCxConvertedValue[bodem+1]/0x0010;
}
}
else{
for(bodem=dem1;bodem<dem2;bodem++){
if(uhADCxConvertedValue[bodem]<50) xungthap++; else xungcao++;
	dorong=(bodem-dem1);
dulieuve[dorong]=uhADCxConvertedValue[bodem+1]/0x0010;
}
}

drawfige(&dulieuve[0]);	
print1("xung cao",30,110,0);
Display_Value(xungcao,30,130);
print1("xung thap",30,150,0);
Display_Value(xungthap,30,170);
_delay_ms(300);
  

       }
		
		
  */
	
	
  {/*
	Display_Value(uhADCxConvertedValue[0],30,30);
		Display_Value(uhADCxConvertedValue[1],30,50);
		Display_Value(uhADCxConvertedValue[2],30,70);
		Display_Value(uhADCxConvertedValue[3],30,90);
		Display_Value(uhADCxConvertedValue[4],30,110);
		Display_Value(uhADCxConvertedValue[5],30,130);
		Display_Value(uhADCxConvertedValue[6],30,150);
		Display_Value(uhADCxConvertedValue[7],30,170);
		Display_Value(uhADCxConvertedValue[8],30,210);
	}
	{*/
for(bodem=0;bodem<300;bodem++) {mang_dothi[bodem]=1+ uhADCxConvertedValue[bodem+1]/20;}
drawfige(&mang_dothi[0]);
_delay_ms(200);
	drawfige_e(&mang_dothi[0]);
}		
while (uhADCxConvertedValue[2300]==0);
		for(bodem=0;bodem<24000;bodem++){
		uhADCxConvertedValue[bodem]=0;
             }
		while (uhADCxConvertedValue[1]==0);
		for(bodem=0;bodem<24000;bodem++){
		uhADCxConvertedValue[bodem]=0;
             }				 
		while (uhADCxConvertedValue[2300]==0);				 
		for(bodem=0;bodem<24000;bodem++){
		uhADCxConvertedValuex[bodem]=uhADCxConvertedValue[bodem];
             }
						 
						 
						 
						 ......................
						 
		
		lamlai:						 
		dem1=0;dem2=0; 
		for(bodem=1000;bodem<12000;bodem++) {
			if((uhADCxConvertedValue[bodem]>2000)&&(uhADCxConvertedValue[bodem+1]<2000)) dem1=bodem+2;
				}
		if(dem1==0) goto lamlai;
		batdau:
		for(bodem=dem1;bodem<23000;bodem++) {
				if((uhADCxConvertedValue[bodem]>2000)&&(uhADCxConvertedValue[bodem+1]<2000)) { dem2=bodem+1; goto hienra;}
				}
		goto batdau;
 
		hienra:
 //for(bodem=0;bodem<300;bodem++) {dulieuve[bodem]=0;}
		dorong=dem2-dem1;
		soxunglap=dorong/250;
		xungthap=0;
		xungcao=0;
		drawfige_e(&mang_dothi[0]);		
		if(soxunglap!=0){
			for(bodem=dem1;bodem<dem2;bodem++){
				if(uhADCxConvertedValue[bodem]<2000) xungthap++; else xungcao++;
				dorong=((bodem-dem1)/soxunglap);
				mang_dothi[dorong]=uhADCxConvertedValue[bodem+1]/20;
				}
				for(;bodem<300;bodem++) mang_dothi[bodem]=0;
			}
		else{
			for(bodem=dem1;bodem<dem2;bodem++){
				if(uhADCxConvertedValue[bodem]<2000) xungthap++; else xungcao++;
				dorong=(bodem-dem1);
				mang_dothi[dorong]=uhADCxConvertedValue[bodem+1]/20;
			}
			}
			
		drawfige(&mang_dothi[0]);	
		print1("xung cao",30,110,0);
		Display_Valuex(xungcao,30,130);
		print1("xung thap",30,150,0);
		Display_Valuex(xungthap,30,170);
_delay_ms(100);
 		for(bodem=0;bodem<24000;bodem++){
		uhADCxConvertedValue[bodem]=0;
             }
			while (uhADCxConvertedValue[0]==0);
		for(bodem=0;bodem<24000;bodem++){
		uhADCxConvertedValue[bodem]=0;
             }	
						 
						 
						 
						void DMA2_Channel3_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA2_IT_HT3)) //half transfer completed
	{ 
		DMA_ClearITPendingBit(DMA2_IT_HT3);
		if(!dmaBufSel)
		{ 	//dmaBufSel = 0, reload new data for waveBuffer1
			res = f_read(&fdst,waveBuffer1, br, &bw); 
		t++ ;
		}
		else
		{	//dmaBufSel != 0, reload new data for waveBuffer0
			res = f_read(&fdst,waveBuffer0, br, &bw); 
				t++ ;
			if(t==3)
			{
			SoundNoData.reLoadSize =16777216*waveBuffer0[11]+65536*waveBuffer0[10]+256*waveBuffer0[9]+waveBuffer0[8] ;//2^0,8,16,24
			printf(" chieu dai cua file nhac la :%d byte \n\r",SoundNoData.reLoadSize) ;
			}
	
		
		}
	}
	else if (DMA_GetITStatus(DMA2_IT_TC3)) 
	{ // transfer completed
		DMA_ClearITPendingBit(DMA2_IT_TC3);	
		if(SoundNoData.reLoadSize < WAVE_DMA_BUFFER_SIZE) 
		{
			// for smooth audio out
			DAC_SetChannel1Data(DAC_Align_8b_R, 0x0);
			waveFlag = wavFinish;
		
		}
		else 
		{	
			SoundNoData.reLoadSize -= WAVE_DMA_BUFFER_SIZE;

			DMA_Cmd(DMA2_Channel3, DISABLE);

			if(dmaBufSel) 
			{	// dmaBufSel != 0, play wave from waveBuffer0
				waveDMA_InitStructure.DMA_MemoryBaseAddr =(uint32_t)waveBuffer0;
			}
			else	// dmaBufSel = 0, play wave from waveBuffer1
			{
				waveDMA_InitStructure.DMA_MemoryBaseAddr =(uint32_t)waveBuffer1; 
			}

			// switch dmaBuffer from 0 to 1 and vi vesa; to switch 2 buffer each other
			dmaBufSel = 1 - dmaBufSel;
			
			DMA_Init(DMA2_Channel3,  &waveDMA_InitStructure);
			DMA_Cmd( DMA2_Channel3, ENABLE);

		}
	}
}
 
						 
				Display_Value(uhADCxConvertedValue[0],30,10);
    Display_Value(uhADCxConvertedValue[100],30,30);
		Display_Value(uhADCxConvertedValue[200],30,50);
		Display_Value(uhADCxConvertedValue[300],30,70);
		Display_Value(uhADCxConvertedValue[400],30,90);
		Display_Value(uhADCxConvertedValue[600],30,110);
		Display_Value(uhADCxConvertedValue[1110],30,130);
		Display_Value(giatri,30,150);
	
		giatri++;
}
		} {				 
						 
						 