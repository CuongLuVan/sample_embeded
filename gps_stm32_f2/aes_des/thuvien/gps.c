



void open_raw_image(char *filename){
uint16_t duara,men;
	uint32_t  giatri;
	char asu[20];
FRESULT res;	
	
f_mount(&FatFs, "", 0);		/* Give a work area to the default drive */
      f_open(&Fil,filename, FA_OPEN_EXISTING | FA_READ);
		
		res = f_read(&Fil, Buff,7680, &bw);
				for(giatri=0;giatri<3840;giatri++) {
				anhkhung[giatri]=Buff[giatri*2]*0x0100+Buff[giatri*2+1];
				}	
				drawBitmap1(0,228,320,12,&anhkhung[0],1);
				
      for(duara=239;duara>10;duara-=11){
					res = f_read(&Fil, Buff,7040, &bw);
					for(giatri=0;giatri<320;giatri++) {
						anhkhung[giatri]=anhkhung[3520+giatri];
					}	
					for(giatri=0;giatri<3520;giatri++) {
						anhkhung[giatri+320]=Buff[giatri*2]*0x0100+Buff[giatri*2+1];
					}			
			drawBitmap1(0,duara-22,320,12,&anhkhung[0],1);
	//		_delay_ms(20);
	}
		f_close(&Fil);								/* Close the file */
	_delay_ms(100);		
//NOKIA5110_GotoXY(0,0);
  //NOKIA5110_Puts("hello");
}


