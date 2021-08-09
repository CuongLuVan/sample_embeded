#include "define_thread.h"
#include "processmodel.h"
#include "debug.h"
#include "structcommunicatedata.h"
#include "Define_Api.h"
static DataJoyStick mdata_joystick;
static DataBLDC mBldc_L;
static DataBLDC mBldc_R;
static DataBLDC check_warning_BLDC;
static DataSensor mdata_Sensor;
static DataSensor Sensor_mpu_6050;
static HighLevelIncident hCheck_Joystick,hCheck_Slave,hCheck_Sensor;
static MediumLevelIncident mCheck_Joystick,mCheck_Slave,mCheck_Sensor;
static LowLevelIncident lCheck_Joystick,lCheck_Slave,lCheck_Sensor;
HighLevelIncident *wh_from_sensor,*wh_from_slave,*wh_from_joystick;
MediumLevelIncident *wm_from_sensor,*wm_from_slave,*wm_from_joystick;
LowLevelIncident   *wl_from_sensor,*wl_from_slave,*wl_from_joystick;

//#include "Define_Api.h"
ProcessModel::ProcessModel() {

}

ProcessModel::~ProcessModel() {

}



 void ProcessModel::setTimeout_20ms(int lparam, int hparam, void * pointer, void *data){
    Debug::getInstance()->debugdata("START timer20msCallBack");
    //ProcessControl::getInstance()->sendTimeout20ms(lparam,lparam,pointer,data);
    Debug::getInstance()->debugdata("END timer20msCallBack");
 }
 void ProcessModel::sendRequest(int lparam, int hparam, void * pointer, void *data) {

 }


 /*START Nguyen Dang Quang 22/08/2017*/
 // sau khi phát hiện có wanning sẽ  phân loại wanning, nếu là high thì stop động cơ
 /*void ProcessModel::Process(int lparam, int hparam, void * pointer, void *data){
     DWORD *datapointer;
     datapointer=(DWORD *)(data);
     DWORD *Poiter;
     Poiter=(DWORD *)(pointer);

    int check;
    check = checkWarning(lparam,hparam,pointer,data);
   if(check==1){
          if(lparam==VALUE_OK_INVALID){
            if(hparam==FROM_COMMUNICATE_TASK)
            {
                if(NOMAL_FROM_JOYSTICK==true){
                    processDataJoyStick( lparam,hparam, pointer,data);
                }
                else
                if(NOMAL_FROM_SENSOR==true){
                    processDataSensor( lparam,hparam, pointer,data);
                }
                else
                if(NOMAL_FROM_SLAVE==true){
                    processDataBldc( lparam,hparam, pointer,data);
                }
            }
            if(hparam==NOMAL_FROM_AUDIO_TASK){
                    processDataAudio( lparam,hparam, pointer,data);
            }
            if(hparam==NOMAL_FROM_SCREEN_TASK){
                    processDataScreen( lparam,hparam, pointer,data);
            }
   }
   else{
        classifyWarning( lparam,  hparam, pointer, data);
        if(lparam==GROUP_WARNING_MEDIUM){
            if(hparam==FROM_COMMUNICATE_TASK)
            {
                if(WARNING_FROM_JOYSTICK==true){
                    processDataJoyStick( lparam,hparam, pointer,data);
                }
                else
                if(WARNING_FROM_SENSOR==true){
                    processDataSensor( lparam,hparam, pointer,data);
                }
                else
                if(WARNING_FROM_SLAVE==true){
                    processDataBldc( lparam,hparam, pointer,data);
                }
            }
            if(hparam==WARNING_FROM_AUDIO_TASK){
                    processDataAudio( lparam,hparam, pointer,data);
            }
            if(hparam==WARNING_FROM_SCREEN_TASK){
                    processDataScreen( lparam,hparam, pointer,data);
            }
        }
        if(lparam==GROUP_WARNING_LOW){
             if(hparam==FROM_COMMUNICATE_TASK)
             {
                if(WARNING_FROM_JOYSTICK==true){
                    processDataJoyStick( lparam,hparam, pointer,data);
                }
                else
                if(WARNING_FROM_SENSOR==true){
                    processDataSensor( lparam,hparam, pointer,data);
                }
                else
                if(WARNING_FROM_SLAVE==true){
                    processDataBldc( lparam,hparam, pointer,data);
                }
            }
            if(hparam==WARNING_FROM_AUDIO_TASK){
                    processDataAudio( lparam,hparam, pointer,data);
            }
            if(hparam==WARNING_FROM_SCREEN_TASK){
                    processDataScreen( lparam,hparam, pointer,data);
            }

       }
    }
   }
 }*/
   /* if(lparam==GROUP_WARNING_HIGHT){
        stopProcess(lparam,  hparam, pointer, data);


    else {
  //  do{
    //check_sensor(check_to_Restart_sensor ,0, pointer,data);
//    check_bldc( check_to_Restart_bldc,0, pointer,data);
//    check_joystick( check_to_Restart_joystick,0, pointer,data);
   // if(check_to_Restart_sensor==1&&check_to_Restart_bldc==1&&check_to_Restart_joystick==1)
  //      check_to_Restart==1;
  //  }
  //  while(
    //      check_to_Restart==1);


*/
 void ProcessModel::stopProcess(int lparam, int hparam, void * pointer, void *data) {
        stopGas( lparam,  lparam, pointer, data);
}
 void ProcessModel::stopGas(int lparam, int hparam, void * pointer, void *data){
     float gas;
     gas = 0;
 }
 /*END Nguyen Dang Quang 22/08/2017*/
 void ProcessModel::readStatusBldc(int lparam, int hparam, void * pointer, void *data) {

 }
 /*START Nguyen Dang Quang 23/08/2017*/
 void ProcessModel::processWarningDataBldc(int lparam, int hparam, void * pointer, void *data){

 }
 void ProcessModel::processWarningDataSensor(int lparam, int hparam, void * pointer, void *data){

 }
 void ProcessModel::processWarningDataJoystick(int lparam, int hparam, void * pointer, void *data){

 }

 void ProcessModel::processDataBldc(int lparam, int hparam, void * pointer, void *data) {
         int check;
         check = checkWarning(lparam, hparam, pointer, data);
         if (check ==1) {
             DataBLDC *databldc=(DataBLDC*) data;
             mBldc_L.leng=databldc->leng;
             mBldc_L.lengt=databldc->lengt;
             mBldc_L.vehicleControl=databldc->vehicleControl;
             mBldc_L.vehicleCurent=databldc->vehicleCurent;
             mBldc_L.warning=databldc->warning;

             mBldc_R.leng=databldc->leng;
             mBldc_R.lengt=databldc->lengt;
             mBldc_R.vehicleControl=databldc->vehicleControl;
             mBldc_R.vehicleCurent=databldc->vehicleCurent;
             mBldc_R.warning=databldc->warning;
         }
 }

 void ProcessModel::processDataSensor(int lparam, int hparam, void * pointer, void *data){
         int check;
         if(lparam==VALUE_OK_INVALID){
        check = checkWarning(lparam, hparam, pointer, data);
         if (check == 1) {
         DataSensor *dataSensor =(DataSensor*) data;
         mdata_Sensor.distanceB=dataSensor->distanceB;
         mdata_Sensor.distanceF=dataSensor->distanceF;
         mdata_Sensor.distanceL=dataSensor->distanceL;
         mdata_Sensor.distanceR=dataSensor->distanceR;

         mdata_Sensor.sensor_humi=dataSensor->sensor_humi;
         mdata_Sensor.sensor_light=dataSensor->sensor_light;
         mdata_Sensor.sensor_pressure=dataSensor->sensor_pressure;
         mdata_Sensor.sensor_temp=dataSensor->sensor_temp;

         mdata_Sensor.value_acceleration=dataSensor->value_acceleration;
         mdata_Sensor.warning=dataSensor->warning;

 }
 }
}
 /*END Nguyen Dang Quang 23/08/2017*/
 void ProcessModel::processDataScreen(int lparam, int hparam, void * pointer, void *data) {
     int check;
     check = checkWarning(lparam, hparam, pointer, data);
     if (check = 1) {
         processData(lparam, hparam, pointer, data);
     }
     else{

         /*START vu tri minh 20/08/2017*/
          Debug::getInstance()->debugdata("Warning : sent message to  screen !");
          }
            /*END vu tri minh 20/08/2017*/
 }
 void ProcessModel::processDataAudio(int lparam, int hparam, void * pointer, void *data){
     int check;
     check = checkWarning(lparam, hparam, pointer, data);
     if (check = 1) {
         processData(lparam, hparam, pointer, data);
     }
     else{
         /*START vu tri minh 20/08/2017*/
          Debug::getInstance()->debugdata("Warning : sent message to  audio !");
     }
                /*END vu tri minh 20/08/2017*/
 }
 void ProcessModel::ProcessDataCommunicate(int lparam, int hparam, void * pointer, void *data){
     int check;
     check = checkWarning(lparam, hparam, pointer, data);
     if (check = 1) {
         processData(lparam, hparam, pointer, data);
     }
 }
  void ProcessModel::processData(int lparam, int hparam, void * pointer, void *data) {
      /*START luvan cuong 19/8/2017*/
      if(mdata_joystick.warning == NO_WARNING){
          if(mdata_Sensor.warning == NO_WARNING){
             mBldc_L.vehicleControl = 20*mdata_joystick.y+14*mdata_joystick.x;
             mBldc_R.vehicleControl = 20*mdata_joystick.y-14*mdata_joystick.x;
          }
      }
    /*END luvan cuong 19/8/2017*/

 }
 void ProcessModel::processDataJoyStick(int lparam, int hparam, void * pointer, void *data) {
     /*START luvan cuong 19/8/2017*/
     if(lparam==VALUE_OK_INVALID){
         DataJoyStick *datajoyStick=(DataJoyStick *) data;
         if(datajoyStick->enable==false){
            mdata_joystick.enable=false;
         }
         else
         {
              mdata_joystick.enable=true;
              mdata_joystick.x = datajoyStick->x;
              mdata_joystick.y = datajoyStick->y;
              mdata_joystick.warning = datajoyStick->warning;
         }
     }
     if(hparam==JOYSTICK_MECHANIC_COMMUNICATE_COMMAND_F1){
        if(mdata_joystick.enable==false){
             DataJoyStick *datajoyStick=(DataJoyStick *) data;
             mdata_joystick.x = datajoyStick->x;
             mdata_joystick.y = datajoyStick->y;
        }
     }
     /*END luvan cuong 19/8/2017*/
 }

    /*START vu tri minh 20/08/2017*/
 int ProcessModel::checkWarning(int lparam, int hparam, void * pointer, void *data)
 {
     int check;
     if(mdata_joystick.warning == NO_WARNING &&
        mdata_Sensor.warning == NO_WARNING &&
        check_warning_BLDC.warning == NO_WARNING){
         check = 1;
     }
     else{
         check = 0;
     }
     lparam=check;
     return lparam;
 }
 /*START Nguyen Dang Quang 22/08/2017*/
 bool ProcessModel::checkSensor(int lparam, int hparam, void * pointer, void *data){
     if(lparam==VALUE_OK_INVALID)
         return 1;
 }
 bool ProcessModel::checkJoystick(int lparam, int hparam, void * pointer, void *data){
     if(lparam==VALUE_OK_INVALID)
         return 1;
 }
 bool ProcessModel::checkBldc(int lparam, int hparam, void * pointer, void *data){
     if(lparam==VALUE_OK_INVALID)
         return 1;
 }
 /*END Nguyen Dang Quang 22/08/2017*/
 int ProcessModel::classifyWarning(int lparam, int hparam, void *pointer, void *data){
     int checkStatus;
      checkStatus=checkWarning( lparam, hparam,  pointer, data);
     if (checkStatus==0)
     {
      if(lparam == GROUP_WARNING_HIGHT){
          if(hparam == WARNING_FROM_JOYSTICK){

               HighLevelIncident *dataPointer_hJoysticks = (HighLevelIncident *)pointer;

                if(dataPointer_hJoysticks->address == H_ENUM_HANGED_BUTTONSENSOR){
                hCheck_Joystick.code_incident = 1;
                }
                if(dataPointer_hJoysticks->address == H_ENUM_HOLE){
                hCheck_Joystick.code_incident = 2;
                }
                if(dataPointer_hJoysticks->address == H_ENUM_IMPEDIMENT){
                hCheck_Joystick.code_incident = 3;
                }
                if(dataPointer_hJoysticks->address == H_ENUM_OUT_IMPACT){
                hCheck_Joystick.code_incident = 4;
                }
                if(dataPointer_hJoysticks->address == H_ENUM_STAIR_SLIDE){
                hCheck_Joystick.code_incident = 5;
                }
          }
           if(hparam == WARNING_FROM_SLAVE){

               HighLevelIncident *dataPointer_hSlave = (HighLevelIncident *)pointer;

               if(dataPointer_hSlave->address == H_SLAVE_CHECK_HALL){
               hCheck_Slave.code_incident = 1;
               }
               if(dataPointer_hSlave->address == H_SLAVE_DIRECTION){
               hCheck_Slave.code_incident = 2;
               }
               if(dataPointer_hSlave->address == H_SLAVE_OVER_CURRENT){
               hCheck_Slave.code_incident = 3;
               }
               if(dataPointer_hSlave->address == H_SLAVE_RUN_MOTOR){
               hCheck_Slave.code_incident = 4;
               }
           }
           if(hparam == WARNING_FROM_SENSOR){

               HighLevelIncident *dataPointer_hSensor = (HighLevelIncident *)pointer;

               if(dataPointer_hSensor->address == H_SENSORS_HOLE){
               hCheck_Sensor.code_incident = 1;
               }
               if(dataPointer_hSensor->address == H_SENSORS_IMPEDIMENT){
               hCheck_Sensor.code_incident = 2;
               }
               if(dataPointer_hSensor->address == H_SENSORS_OUT_IMPACT){
               hCheck_Sensor.code_incident = 3;
               }
               if(dataPointer_hSensor->address == H_SENSORS_SPIN_AROUND){
               hCheck_Sensor.code_incident = 4;
               }
               if(dataPointer_hSensor->address == H_SENSORS_STAIR_SLIDE){
               hCheck_Sensor.code_incident = 5;
               }
               if(dataPointer_hSensor->address == H_SENSORS_ZICZAG){
               hCheck_Sensor.code_incident = 6;
               }
       }
      }
      if(lparam == GROUP_WARNING_MEDIUM){
          if(hparam == WARNING_FROM_JOYSTICK){

            MediumLevelIncident *dataPointer_mJoystick = (MediumLevelIncident *)pointer;

              if(dataPointer_mJoystick->address == M_ENUM_DOWNGRADE){
              mCheck_Joystick.code_incident = 1;
              }
              if(dataPointer_mJoystick->address == M_ENUM_MCU_HANG){
              mCheck_Joystick.code_incident = 2;
              }
              if(dataPointer_mJoystick->address == M_ENUM_POTHOLE){
              mCheck_Joystick.code_incident = 3;
              }
              if(dataPointer_mJoystick->address == M_ENUM_USER_STROKE){
              mCheck_Joystick.code_incident = 4;
              }
          }
           if(hparam == WARNING_FROM_SLAVE){
               MediumLevelIncident *dataPointer_mSlave = (MediumLevelIncident *)pointer;

                 if(dataPointer_mSlave->address == M_SLAVE_HANGED_SENSOR){
                 mCheck_Slave.code_incident = 1;
                 }
                 if(dataPointer_mSlave->address == M_SLAVE_OVER_TEMPERATURE){
                 mCheck_Slave.code_incident = 2;
                }
           }
           if(hparam == WARNING_FROM_SENSOR){

               MediumLevelIncident *dataPointer_mSensor = (MediumLevelIncident *)pointer;

                 if(dataPointer_mSensor->address == M_SENSORS_DOWNGRADE){
                 mCheck_Sensor.code_incident = 1;
                 }
                 if(dataPointer_mSensor->address == M_SENSORS_HANGED_MCU){
                 mCheck_Sensor.code_incident = 2;
                 }
                 if(dataPointer_mSensor->address == M_SENSORS_MPU6050_ERROR){
                 mCheck_Sensor.code_incident = 3;
                 }
                 if(dataPointer_mSensor->address == M_SENSORS_POTHOLE){
                 mCheck_Sensor.code_incident = 4;
                 }
       }

      }
      if(lparam == GROUP_WARNING_LOW){
          if(hparam == WARNING_FROM_JOYSTICK){

              LowLevelIncident *dataPointer_lJoystick = (LowLevelIncident *)pointer;

              if(dataPointer_lJoystick->address == L_ENUM_BUMPY_WAY){
              lCheck_Sensor.code_incident = 1;
              }
              if(dataPointer_lJoystick->address == L_ENUM_DRAGED_SENSOR){
              lCheck_Sensor.code_incident = 2;
              }
              if(dataPointer_lJoystick->address == L_ENUM_SPIN_AROUND){
              lCheck_Sensor.code_incident = 3;
              }
          }
           if(hparam == WARNING_FROM_SLAVE){

               LowLevelIncident *dataPointer_lSlave = (LowLevelIncident *)pointer;

               if(dataPointer_lSlave->address == L_SLAVE_UNDERSTAND){
               lCheck_Slave.code_incident = 1;
               }
           }
           if(hparam == WARNING_FROM_SENSOR){

               MediumLevelIncident *dataPointer_lSensor = (MediumLevelIncident *)pointer;

                 if(dataPointer_lSensor->address == L_SENSORS_BUMPY_WAY){
                 lCheck_Sensor.code_incident = 1;
                 }
                 if(dataPointer_lSensor->address == L_SENSORS_HUMIDITY){
                 lCheck_Sensor.code_incident = 2;
                 }
                 if(dataPointer_lSensor->address == L_SENSORS_LIGHT){
                 lCheck_Sensor.code_incident = 3;
                 }
                 if(dataPointer_lSensor->address == L_SENSORS_OVER_SAFETEMP){
                 lCheck_Sensor.code_incident = 4;
                 }
                 if(dataPointer_lSensor->address == L_SENSORS_PRESSURE){
                 lCheck_Sensor.code_incident = 5;
                 }
                 if(dataPointer_lSensor->address == L_SENSORS_SENSOR_ERROR){
                 lCheck_Sensor.code_incident = 6;
                 }
                 if(dataPointer_lSensor->address == L_SENSORS_SUPERSONIC_L){
                 lCheck_Sensor.code_incident = 7;
                 }
                 if(dataPointer_lSensor->address == L_SENSORS_SUPERSONIC_R){
                 lCheck_Sensor.code_incident = 8;
                 }
       }
  }
     }
 }
