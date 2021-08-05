while (1)
	{	readadc();		
		_delay_ms(80);
    dem1=0;dem2=0; 
		for(bodem=1;bodem<24000;bodem++) {
			if((uhADCxConvertedValue[bodem]>1000)&&(uhADCxConvertedValue[bodem+1]<1000)) { dem1=bodem+1;  break;}
				}
		if(dem1!=0){
        for(bodem=dem1;bodem<24000;bodem++) {
				if((uhADCxConvertedValue[bodem]>1000)&&(uhADCxConvertedValue[bodem+1]<1000)) { dem2=bodem+1; break;}
				}
       dorong=dem2-dem1;
		soxunglap=dorong/250;
		xungthap=0;
		xungcao=0;
		drawfige_e(&mang_dothi[0]);		
		if(soxunglap!=0){
			for(bodem=dem1;bodem<dem2;bodem++){
				if(uhADCxConvertedValue[bodem]<1000) xungthap++; else xungcao++;
				dorong=((bodem-dem1)/soxunglap);
				mang_dothi[dorong]=uhADCxConvertedValue[bodem+1]/20;
				}
			}
		else{
			for(bodem=dem1;bodem<dem2;bodem++){
				if(uhADCxConvertedValue[bodem]<1000) xungthap++; else xungcao++;
				dorong=(bodem-dem1);
				mang_dothi[dorong]=uhADCxConvertedValue[bodem+1]/20;
			}
			}
			
		drawfige(&mang_dothi[0]);	
		//print1("xung cao",30,110,0);
		Display_Valuex(xungcao,30,130);
		//print1("xung thap",30,150,0);
		Display_Valuex(xungthap,30,170);
		//Display_Value(dem1,110,130);
    //Display_Value(dem2,110,150);			
      } else 
		{
drawfige_e(&mang_dothi[0]);
   for(bodem=0;bodem<48000;bodem+=200)
			mang_dothi[bodem/200]=uhADCxConvertedValue[bodem+1]/20;
  drawfige(&mang_dothi[0]);
    }
		xak=0;
		addd_fu();
   
			_delay_ms(100);
      }		
	// doan code tren la mo ta ve do thi