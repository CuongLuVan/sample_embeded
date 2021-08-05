o#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
SemaphoreHandle_t xBinarySemaphore;
byte interruptPin = 12;
volatile byte state = LOW;
byte ledPin = 14;


void setup() {
  Serial.begin(112500);
  pinMode(ledPin, OUTPUT);
  /* set the interrupt pin as input pullup*/
  pinMode(interruptPin, INPUT_PULLUP);
  Serial.println("Hello from task taskControl");
  attachInterrupt(digitalPinToInterrupt(interruptPin), ISRcallback, CHANGE);
  /* initialize binary semaphore */
  xBinarySemaphore = xSemaphoreCreateBinary();

   xTaskCreate(taskControl,  "TaskControl", 10000,NULL, 1, NULL);
  xTaskCreate( taskSensor,  "TaskSensor",   10000,NULL, 4, NULL);
  xTaskCreate(taskWifi,  "TaskWifi",    10000,NULL, 2, NULL);
  xTaskCreate(taskCommunicate,  "TaskCommunicate",    10000,NULL, 3, NULL);       
}

void loop() {
  delay(1000);
}

void ISRcallback() {
  /* */
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  /* un-block the interrupt processing task now */
  xSemaphoreGiveFromISR( xBinarySemaphore, &xHigherPriorityTaskWoken );
}

int buttonAction=0;
void taskControl( void * parameter )
{
    while(1){
     // buttonAction=controlDevice.checkButton();
        xSemaphoreTake( xBinarySemaphore, portMAX_DELAY );
        Serial.println("Hello from task taskControl");
        delay(100);
        xSemaphoreGive( xBinarySemaphore );
        delay(100);
    }
    vTaskDelete( NULL );
}


void taskSensor( void * parameter )
{
    while(1){
          xSemaphoreTake( xBinarySemaphore, portMAX_DELAY );
          Serial.println("ISRprocessing is running");
          /* toggle the LED now */
          state = !state;
          digitalWrite(ledPin, state);
          Serial.println("Hello from task taskSensor");
          delay(1000);
          xSemaphoreGive( xBinarySemaphore );
    }
    vTaskDelete( NULL );
}
 
void taskWifi( void * parameter)
{
    while(1){
       // clientHttpEsp.loopEsp32();
        Serial.println("Hello from task taskWifi");
        delay(1000);
    }
    vTaskDelete( NULL );
}

void taskCommunicate( void * parameter)
{
   while(1){
 
        Serial.println("Hello from task taskCommunicate");
        delay(1000);
    }
    vTaskDelete( NULL );
}
