/*
file:  control.c
description : control all compoment of device
Create date : 19/2/2017
user cread : Lu Van Cuong
*/
#include "debug.h" 
#include "control.h"
#include "ADCsensor.h"
#include "i2csensor.h"
#include "define.h"
#include "communication.h"

static DataSensorStruct mdatatosend;
static uint16_t mcounterdata=0;
static SampleDataSensorStruct mdatatosave;

extern void UART_SendChar(char ch);
extern void setupUart(int BaudRate);
/*****************************************************************************
function:  getAllDataSensor
argunent: data
return : State
description : function to get all value sensor
Create date : 19/2/2017
user cread : Lu Van Cuong
******************************************************************************/
uint8_t getAllDataSensor(void){
	uint32_t valuedataair;

	printDebug("End:uint8_t getAllDataSensor"); 
	mcounterdata++;
	valuedataair=sensorGetHumidity_TemperatureResult();
  mdatatosave.temperature+=(valuedataair)&0xffff;
  mdatatosave.humidity+=(valuedataair>>16)&0xffff;
  mdatatosave.pressure+=getDataPressureSensorBM085();//getDataPressureSensor();
	printDebug1("START:uint8_t pressure  =>%d",mdatatosave.pressure);
  mdatatosave.verhicle+=sensorWindyResult();
	if(mcounterdata>999){
		mdatatosend.temperature=(uint16_t) mdatatosave.temperature*10/mcounterdata;
		mdatatosend.humidity=(uint16_t) mdatatosave.humidity*10/mcounterdata;
		mdatatosend.pressure=(uint32_t) mdatatosave.pressure*10/mcounterdata;
		mdatatosend.verhicle=(uint32_t) mdatatosave.verhicle*10/mcounterdata;
		mdatatosend.start=0x34;
		mdatatosend.light=0xb5;
		printDebug1("START:uint8_t temperature=>%d",mdatatosend.temperature); 
		printDebug1("START:uint8_t humidity=>%d",mdatatosend.humidity); 
		printDebug1("START:uint8_t pressure=>%d",mdatatosend.pressure); 
		printDebug1("START:uint8_t getAllDataSensor=>%d",mdatatosend.verhicle); 
		mcounterdata=0;
		mdatatosave.temperature=0;
		mdatatosave.humidity=0;
		mdatatosave.pressure=0;
		mdatatosave.verhicle=0;
		return 1;
	}
	
  return 0;
}


void setupAllCompoment(void){
	printDebug("START:~~~~~~~setupAllCompoment1");
	initI2CPressure();
	printDebug("START:~~~~~~~setupAllCompoment2");
	setupAllADCSensor();
	printDebug("START:~~~~~~~setupAllCompoment3");
	setupUart(9600);
}

void sendUARTData(void){
int i;
	uint8_t *data;
	data=(uint8_t *)&mdatatosend.start;
	for(i=0;i<sizeof(DataSensorStruct);i++){
		UART_SendChar((char ) *data);
		data=data+1;
	}

}
