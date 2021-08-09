
/*****************************************************************************
function:  process
argunent: void
return : int
description : process function
Create date : 23/7/2017
user cread : Nguyen Dang Quang
***************************************************************/


#include "processControl.h"
#include "processModel.h"
//#include "Define_Api.h"
#include "debug.h"
#include "common.h"
#include "define_thread.h"
#include "structcommunicatedata.h"
#include "Audio/audio.h"

//ProcessModel *ProcessModel::INSTANCEDATA=NULL;
Common *Common::INSTANCEDATA=NULL;

int ProcessControl::flag_control=0;				//
DWORD ProcessControl::main_thread=0;			//
DWORD ProcessControl::Audio_thread=0;
DWORD ProcessControl::Communicate_thread=0;
DWORD ProcessControl::Screen_thread=0;

static DataRequestConfirm dataconfirm;			//
static DataCommand content;						// content is a variable of DataCommand

ProcessControl::ProcessControl() {

}

ProcessControl::~ProcessControl() {

}

        /*START Nguyen Dang Quang 24/08/2017*/
void ProcessControl::execute(int lparam, int hparam, void *pointer, void *data){  //giai ma du lieu, xet xem du lieu thuoc thream nao sau do luu vao bien cua thread day
    DWORD *datapointer;				// pointer 32bit
    Debug::getInstance()->debugdata("START ProcessControl::execuse");	// debug
    if(lparam==VALUE_OK_INVALID){		  // if ok

        if(hparam==MAIN_THEAD){				// if from main_thread
            Debug::getInstance()->debugdata("START main_thread");
            datapointer=(DWORD *)(data);    // main thread chi can 32bit de ma hoa cau lenh
            main_thread = *datapointer;		// main_thread lay'du lieu cau lenh duoc ma hoa
            Debug::getInstance()->debugdata("END main_thread",main_thread);
            //UINT TimerId = SetTimer(NULL, 0, 5000, &timer20msCallBack);				//2000 milliseconds
        }
        else
        if(hparam==FROM_COMMUNICATE_TASK)
        {
            DWORD *datapointer;
            datapointer=(DWORD *)(data);
            DWORD *Poiter;
            Poiter=(DWORD *)(pointer);

           int check;
           check = ProcessModel::getInstance()->checkWarning(lparam,hparam,pointer,data);
          if(check==1){
                 if(lparam==VALUE_OK_INVALID){
                   if(hparam==FROM_COMMUNICATE_TASK)
                   {
                       if(NOMAL_FROM_JOYSTICK==true){
                           ProcessModel::getInstance()->processDataJoyStick( lparam,hparam, pointer,data);
                       }
                       else
                       if(NOMAL_FROM_SENSOR==true){
                           ProcessModel::getInstance()->processDataSensor( lparam,hparam, pointer,data);
                       }
                       else
                       if(NOMAL_FROM_SLAVE==true){
                           ProcessModel::getInstance()->processDataBldc( lparam,hparam, pointer,data);
                       }
                   }
                   if(hparam==NOMAL_FROM_AUDIO_TASK){
                           ProcessModel::getInstance()->processDataAudio( lparam,hparam, pointer,data);
                   }
                   if(hparam==NOMAL_FROM_SCREEN_TASK){
                           ProcessModel::getInstance()->processDataScreen( lparam,hparam, pointer,data);
                   }
          }
          else{
               ProcessModel::getInstance()->classifyWarning( lparam,  hparam, pointer, data);
               if(lparam==GROUP_WARNING_MEDIUM){
               ProcessControl::MediumLevelIncident *dataCommandToProcess = (ProcessControl::MediumLevelIncident *)data;
                           ProcessControl *point_data_PM = (ProcessControl *)pointer;                       

                                           // Solution for Joystick
                                           if(point_data_PM->hCheck_Joystick.code_incident == 1){
                                               Audio::getInstance()->warningAudio( lparam, hparam,  pointer, data);
                                               ProcessModel::getInstance()->processWarningDataJoystick( lparam, hparam,  pointer, data);

                                               Debug::getInstance()->debugdata("Solution hWarning joystick 1");
                                           }
                                           if(point_data_PM->hCheck_Joystick.code_incident == 2){
                                               Audio::getInstance()->warningAudio( lparam, hparam,  pointer, data);
                                               ProcessModel::getInstance()->processWarningDataJoystick( lparam, hparam,  pointer, data);
                                               Debug::getInstance()->debugdata("Solution hWarning joystick 2");
                                           }
                                           if(point_data_PM->hCheck_Joystick.code_incident == 3){
                                               Audio::getInstance()->warningAudio( lparam, hparam,  pointer, data);
                                               ProcessModel::getInstance()->processWarningDataJoystick( lparam, hparam,  pointer, data);
                                               Debug::getInstance()->debugdata("Solution hWarning joystick 3");
                                           }
                                           if(point_data_PM->hCheck_Joystick.code_incident == 4){
                                               Audio::getInstance()->warningAudio( lparam, hparam,  pointer, data);
                                               ProcessModel::getInstance()->processWarningDataJoystick( lparam, hparam,  pointer, data);
                                               Debug::getInstance()->debugdata("Solution hWarning joystick 4");
                                           }



                                           // Solution for slave
                                           if(point_data_PM->hCheck_Slave.code_incident == 1){
                                               Audio::getInstance()->warningAudio( lparam, hparam,  pointer, data);
                                               ProcessModel::getInstance()->processWarningDataBldc( lparam, hparam,  pointer, data);
                                               Debug::getInstance()->debugdata("Solution hWarning Slave 1");
                                           }
                                           if(point_data_PM->hCheck_Slave.code_incident == 2){
                                               Audio::getInstance()->warningAudio( lparam, hparam,  pointer, data);
                                               ProcessModel::getInstance()->processWarningDataBldc( lparam, hparam,  pointer, data);
                                               Debug::getInstance()->debugdata("Solution hWarning Slave 2");
                                           }


                                           // Solution for Sensor
                                           if(point_data_PM->hCheck_Sensor.code_incident == 1){
                                               Audio::getInstance()->warningAudio( lparam, hparam,  pointer, data);
                                               ProcessModel::getInstance()->processWarningDataSensor( lparam, hparam,  pointer, data);
                                               Debug::getInstance()->debugdata("Solution hWarning Sensor 1");
                                           }
                                           if(point_data_PM->hCheck_Sensor.code_incident == 2){
                                               Audio::getInstance()->warningAudio( lparam, hparam,  pointer, data);
                                               ProcessModel::getInstance()->processWarningDataSensor( lparam, hparam,  pointer, data);
                                               Debug::getInstance()->debugdata("Solution hWarning Sensor 2");
                                           }
                                           if(point_data_PM->hCheck_Sensor.code_incident == 3){
                                               Audio::getInstance()->warningAudio( lparam, hparam,  pointer, data);
                                               ProcessModel::getInstance()->processWarningDataSensor( lparam, hparam,  pointer, data);
                                               Debug::getInstance()->debugdata("Solution hWarning Sensor 3");
                                           }
                                           if(point_data_PM->hCheck_Sensor.code_incident == 4){
                                               Audio::getInstance()->warningAudio( lparam, hparam,  pointer, data);
                                               ProcessModel::getInstance()->processWarningDataSensor( lparam, hparam,  pointer, data);
                                               Debug::getInstance()->debugdata("Solution hWarning Sensor 4");
                                           }

}



               if(lparam==GROUP_WARNING_LOW){
               ProcessControl::LowLevelIncident *dataCommandToProcess = (ProcessControl::LowLevelIncident *)data;
                           ProcessControl *point_data_PM = (ProcessControl *)pointer;

                                           // Solution for Joystick
                                           if(point_data_PM->hCheck_Joystick.code_incident == 1){
                                               Audio::getInstance()->warningAudio( lparam, hparam,  pointer, data);
                                               ProcessModel::getInstance()->processWarningDataJoystick( lparam, hparam,  pointer, data);
                                               Debug::getInstance()->debugdata("Solution hWarning joystick 1");
                                           }
                                           if(point_data_PM->hCheck_Joystick.code_incident == 2){
                                               Audio::getInstance()->warningAudio( lparam, hparam,  pointer, data);
                                               ProcessModel::getInstance()->processWarningDataJoystick( lparam, hparam,  pointer, data);
                                               Debug::getInstance()->debugdata("Solution hWarning joystick 2");
                                           }
                                           if(point_data_PM->hCheck_Joystick.code_incident == 3){
                                               Audio::getInstance()->warningAudio( lparam, hparam,  pointer, data);
                                               ProcessModel::getInstance()->processWarningDataJoystick( lparam, hparam,  pointer, data);
                                               Debug::getInstance()->debugdata("Solution hWarning joystick 3");
                                           }




                                           // Solution for slave
                                           if(point_data_PM->hCheck_Slave.code_incident == 1){
                                               Audio::getInstance()->warningAudio( lparam, hparam,  pointer, data);
                                               ProcessModel::getInstance()->processWarningDataBldc( lparam, hparam,  pointer, data);
                                               Debug::getInstance()->debugdata("Solution hWarning Slave 1");
                                           }



                                           // Solution for Sensor
                                           if(point_data_PM->hCheck_Sensor.code_incident == 1){
                                               Audio::getInstance()->warningAudio( lparam, hparam,  pointer, data);
                                               ProcessModel::getInstance()->processWarningDataSensor( lparam, hparam,  pointer, data);
                                               Debug::getInstance()->debugdata("Solution hWarning Sensor 1");
                                           }
                                           if(point_data_PM->hCheck_Sensor.code_incident == 2){
                                               Audio::getInstance()->warningAudio( lparam, hparam,  pointer, data);
                                               ProcessModel::getInstance()->processWarningDataSensor( lparam, hparam,  pointer, data);
                                               Debug::getInstance()->debugdata("Solution hWarning Sensor 2");
                                           }
                                           if(point_data_PM->hCheck_Sensor.code_incident == 3){
                                               Audio::getInstance()->warningAudio( lparam, hparam,  pointer, data);
                                               ProcessModel::getInstance()->processWarningDataSensor( lparam, hparam,  pointer, data);
                                               Debug::getInstance()->debugdata("Solution hWarning Sensor 3");
                                           }
                                           if(point_data_PM->hCheck_Sensor.code_incident == 4){
                                               Audio::getInstance()->warningAudio( lparam, hparam,  pointer, data);
                                               ProcessModel::getInstance()->processWarningDataSensor( lparam, hparam,  pointer, data);
                                               Debug::getInstance()->debugdata("Solution hWarning Sensor 4");
                                           }
                                           if(point_data_PM->hCheck_Sensor.code_incident == 5){
                                               Audio::getInstance()->warningAudio( lparam, hparam,  pointer, data);
                                               ProcessModel::getInstance()->processWarningDataSensor( lparam, hparam,  pointer, data);
                                               Debug::getInstance()->debugdata("Solution hWarning Sensor 5");
                                           }
                                           if(point_data_PM->hCheck_Sensor.code_incident == 6){
                                               Audio::getInstance()->warningAudio( lparam, hparam,  pointer, data);
                                               ProcessModel::getInstance()->processWarningDataSensor( lparam, hparam,  pointer, data);
                                               Debug::getInstance()->debugdata("Solution hWarning Sensor 6");
                                           }
                                           if(point_data_PM->hCheck_Sensor.code_incident == 7){
                                               Audio::getInstance()->warningAudio( lparam, hparam,  pointer, data);
                                               ProcessModel::getInstance()->processWarningDataSensor( lparam, hparam,  pointer, data);
                                               Debug::getInstance()->debugdata("Solution hWarning Sensor 7");
                                           }
                                           if(point_data_PM->hCheck_Sensor.code_incident == 8){
                                               Audio::getInstance()->warningAudio( lparam, hparam,  pointer, data);
                                               ProcessModel::getInstance()->processWarningDataSensor( lparam, hparam,  pointer, data);
                                               Debug::getInstance()->debugdata("Solution hWarning Sensor 8");
                                           }

}

           }
          }
        }

                /*END Nguyen Dang Quang 24/08/2017*/



        }
        else
        if(hparam==FROM_AUDIO_TASK)
        {/*START Nguyen Dang Quang 21/08/2017*/
            DataCommand *datacommand=(DataCommand *) pointer;
            Debug::getInstance()->debugdata("START Audio_thread");
            if(datacommand->ID==AUDIO_COMMAND){
                ProcessModel::getInstance()->processDataAudio(VALUE_OK_INVALID,0,pointer,data);
            }
            if(datacommand->ID==1111112){

                ProcessModel::getInstance()->processData(0,0,pointer,data);
            }
            Debug::getInstance()->debugdata("END Audio_thread");
        }
        else
        if(hparam==FROM_SCREEN_TASK)
        {
            DataCommand *datacommand=(DataCommand *) pointer;
            Debug::getInstance()->debugdata("START Screen_thread");
            if(datacommand->ID==SCREEN_DIRECT_COMMAND){
                ProcessModel::getInstance()->processDataScreen(VALUE_OK_INVALID,0,pointer,data);
            }
            if(datacommand->ID==1111113){

                ProcessModel::getInstance()->processData(0,0,pointer,data);
            }
            Debug::getInstance()->debugdata("END Screen_thread");
           /*END Nguyen Dang Quang 21/08/2017*/
        }

    }
  //  Debug::getInstance()->debugdata("END ProcessControl::execuse",*datapointer);


void ProcessControl::sendTimeout20ms(int lparam, int hparam, void * pointer, void *data){ //timeout 20ms
    Debug::getInstance()->debugdata("START ProcessControl::sendTimeout20ms");
    switch (ProcessControl::flag_control)       // gan co
    {
        case 0: {													//case 0 to case 5 is initialzation, case 5 to case 9 is nomal
            content.ID=PROCESS_TO_MAIN_THEAD;						// dia chi
            content.content=SENDTOSPI_CONTROLBLDC1;					// noi dung
            content.detailcontent=0;								//
            content.adresscommand=NULL;								//
            dataconfirm.Data=0;										//
            dataconfirm.Request=0;									//
            sendDatabldc1( 1,  0,(void *) &content, &dataconfirm);		// sendata to bldc1
            break;
        }
        case 1: {
            content.ID=PROCESS_TO_MAIN_THEAD;
            content.content=SENDTOSPI_CONTROLBLDC2;
            content.detailcontent=0;
            content.adresscommand=NULL;
            dataconfirm.Data=0;
            dataconfirm.Request=0;
            sendDatabldc2(lparam, hparam, pointer, data);				// sendata to bldc2
            break;
        }
        case 2: {
            content.ID=PROCESS_TO_MAIN_THEAD;
            content.content=SENDTOSPI_CONTROLSENSOR1;
            content.detailcontent=0;
            content.adresscommand=NULL;
            dataconfirm.Data=0;
            dataconfirm.Request=0;
            sendDataSensor1(lparam, hparam, pointer, data);
            break;
        }
        case 3: {
            content.ID=PROCESS_TO_MAIN_THEAD;
            content.content=SENDTOSPI_CONTROLSENSOR2;
            content.detailcontent=0;
            content.adresscommand=NULL;
            dataconfirm.Data=0;
            dataconfirm.Request=0;
            sendDataSensor2(lparam, hparam, pointer, data);
            break;
        }
        case 4: {
            content.ID=PROCESS_TO_MAIN_THEAD;
            content.content=SENDTOSPI_CONTROLJOYSTICK;
            content.detailcontent=0;
            content.adresscommand=NULL;
            dataconfirm.Data=0;							//du lieu
            dataconfirm.Request=0;						// yeu cau
            sendDataRequetsJostick(lparam, hparam, pointer, data);
            break;
        }
        case 5: {
            DataJoyStick mdata_joystick;
            ProcessModel::getInstance()->processDataJoyStick(VALUE_OK_INVALID,0,NULL,(void *) &mdata_joystick);
            content.ID = PROCESS_TO_MAIN_THEAD;
            content.content = SENDTOSPI_CONTROLJOYSTICK;
            content.detailcontent = START_CONTROL;
            content.adresscommand = START_CONTROL_CHANGE_VALUE;
            dataconfirm.Data = mdata_joystick.x;							// du lieu cua theo truc x,y
            dataconfirm.Request = mdata_joystick.y;
            sendDataRequetsJostick(lparam, hparam, pointer, data);
            break;
        }
        case 6: {
            content.ID=PROCESS_TO_MAIN_THEAD;
            content.content=SENDTOSPI_CONTROLSENSOR1;
            content.detailcontent=0;
            content.adresscommand=NULL;
            dataconfirm.Data=0;
            dataconfirm.Request=0;
            sendDataSensor1(lparam, hparam, pointer, data);
            break;
        }
        case 7: {
            content.ID=PROCESS_TO_MAIN_THEAD;
            content.content=SENDTOSPI_CONTROLSENSOR2;
            content.detailcontent=0;
            content.adresscommand=NULL;
            dataconfirm.Data=0;
            dataconfirm.Request=0;
            sendDataSensor2(lparam, hparam, pointer, data);
            break;
        }
        case 8: {
            content.ID=PROCESS_TO_MAIN_THEAD;
            content.content=SENDTOSPI_CONTROLBLDC1;
            content.detailcontent=0;
            content.adresscommand=NULL;
            dataconfirm.Data=0;
            dataconfirm.Request=0;

            sendDatabldc2(lparam, hparam, pointer, data);
            break;
        }
        case 9: {
            content.ID=PROCESS_TO_MAIN_THEAD;
            content.content=SENDTOSPI_CONTROLBLDC1;
            content.detailcontent=0;
            content.adresscommand=NULL;
            dataconfirm.Data=0;
            dataconfirm.Request=0;
            sendDatabldc2(lparam, hparam, pointer, data);
            break;
        }

        default:
            break;
    }
    ProcessControl::flag_control++;
    if (ProcessControl::flag_control >= 9)  ProcessControl::flag_control = 5;	// khoi tao 1 lan duy nhat'

}
void ProcessControl::sendDatatoProcess(int lparam, int hparam, void * pointer, void *data) {

}
void ProcessControl::reSendDatatoProcess(int lparam, int hparam, void * pointer, void *data) {

}
void ProcessControl::stopProcess(int lparam, int hparam, void * pointer, void *data) {

}
void ProcessControl::sendDatabldc1(int lparam, int hparam, void * pointer, void *data) {// post len main dia chi va du lieu da duoc luu (pointer and data)
    DWORD adress=(DWORD)pointer;				//ep kieu pointer vs data la dia chi 32bit
    DWORD dataset=(DWORD)data;
    DataRequestConfirm *datacomfirm=(DataRequestConfirm *)data;			// ep kieu data cho dung vs datacomfirm
    DataCommand *dataget=(DataCommand *)pointer;						// ep kieu pointer cho dung vs dataget
    Debug::getInstance()->debugdata("START ProcessControl::sendDatabldc1");
    if(lparam==VALUE_OK_INVALID){
        datacomfirm->ID=SENDTOSPI_CONTROLBLDC1;
        datacomfirm->crc=datacomfirm->ID+(unsigned char)(datacomfirm->Data>>16)
            +(unsigned char)(datacomfirm->Data>>8)+(unsigned char)(datacomfirm->Data)
            +(unsigned char)(datacomfirm->Request>>16)+(unsigned char)(datacomfirm->Request>>8)
            +(unsigned char)(datacomfirm->Request);
    }
    Debug::getInstance()->debugdata("END ProcessControl::sendDatabldc1 dataget command",(int)dataget);
    Debug::getInstance()->debugdata("END ProcessControl::sendDatabldc1 adress",adress);
    Debug::getInstance()->debugdata("END ProcessControl::sendDatabldc1 dataset",dataset);

    datacomfirm=(DataRequestConfirm *)data;
    //PostThreadMessage(main_thread,PROCESS_TO_MAIN_THEAD,adress,dataset);		//post len main dia chi va du lieu da duoc luu (pointer and data)
    Debug::getInstance()->debugdata("END ProcessControl::sendDatabldc1");
}

void ProcessControl::sendDatabldc2(int lparam, int hparam, void * pointer, void *data) {
    DWORD adress=(DWORD)pointer;
    DWORD dataset=(DWORD)data;
    DataRequestConfirm *datacomfirm=(DataRequestConfirm *)data;
    DataCommand *dataget=(DataCommand *)pointer;
    Debug::getInstance()->debugdata("START ProcessControl::sendDatabldc2");
    if(lparam==VALUE_OK_INVALID){
        datacomfirm->ID=SENDTOSPI_CONTROLBLDC2;
        datacomfirm->crc=datacomfirm->ID+(unsigned char)(datacomfirm->Data>>16)
            +(unsigned char)(datacomfirm->Data>>8)+(unsigned char)(datacomfirm->Data)
            +(unsigned char)(datacomfirm->Request>>16)+(unsigned char)(datacomfirm->Request>>8)
            +(unsigned char)(datacomfirm->Request);
    }
    Debug::getInstance()->debugdata("END ProcessControl::sendDatabldc1 dataget command",(int)dataget);
    Debug::getInstance()->debugdata("END ProcessControl::sendDatabldc1 adress",adress);
    Debug::getInstance()->debugdata("END ProcessControl::sendDatabldc1 dataset",dataset);

    datacomfirm=(DataRequestConfirm *)data;
    //PostThreadMessage(main_thread,PROCESS_TO_MAIN_THEAD,adress,dataset);
    Debug::getInstance()->debugdata("END ProcessControl::sendDatabldc2");
}

void ProcessControl::sendDataSensor1(int lparam, int hparam, void * pointer, void *data) {
    DWORD adress=(DWORD)pointer;
    DWORD dataset=(DWORD)data;
    DataRequestConfirm *datacomfirm=(DataRequestConfirm *)data;
    DataCommand *dataget=(DataCommand *)pointer;
    Debug::getInstance()->debugdata("START ProcessControl::sendDataSensor1");
    if(lparam==VALUE_OK_INVALID){
        datacomfirm->ID=SENDTOSPI_CONTROLSENSOR1;
        datacomfirm->crc=datacomfirm->ID+(unsigned char)(datacomfirm->Data>>16)
            +(unsigned char)(datacomfirm->Data>>8)+(unsigned char)(datacomfirm->Data)
            +(unsigned char)(datacomfirm->Request>>16)+(unsigned char)(datacomfirm->Request>>8)
            +(unsigned char)(datacomfirm->Request);
    }
    Debug::getInstance()->debugdata("END ProcessControl::sendDatabldc1 dataget command",(int)dataget);
    Debug::getInstance()->debugdata("END ProcessControl::sendDatabldc1 adress",adress);
    Debug::getInstance()->debugdata("END ProcessControl::sendDatabldc1 dataset",dataset);

    datacomfirm=(DataRequestConfirm *)data;
    //PostThreadMessage(main_thread,PROCESS_TO_MAIN_THEAD,adress,dataset);
    Debug::getInstance()->debugdata("END ProcessControl::sendDataSensor1");
}
void ProcessControl::sendDataSensor2(int lparam, int hparam, void * pointer, void *data) {
    DWORD adress=(DWORD)pointer;
    DWORD dataset=(DWORD)data;
    DataRequestConfirm *datacomfirm=(DataRequestConfirm *)data;
    DataCommand *dataget=(DataCommand *)pointer;
    Debug::getInstance()->debugdata("START ProcessControl::sendDataSensor2");
    if(lparam==VALUE_OK_INVALID){
        datacomfirm->ID=SENDTOSPI_CONTROLSENSOR2;
        datacomfirm->crc=datacomfirm->ID+(unsigned char)(datacomfirm->Data>>16)
            +(unsigned char)(datacomfirm->Data>>8)+(unsigned char)(datacomfirm->Data)
            +(unsigned char)(datacomfirm->Request>>16)+(unsigned char)(datacomfirm->Request>>8)
            +(unsigned char)(datacomfirm->Request);
    }
    Debug::getInstance()->debugdata("END ProcessControl::sendDatabldc1 dataget command",(int)dataget);
    Debug::getInstance()->debugdata("END ProcessControl::sendDatabldc1 adress",adress);
    Debug::getInstance()->debugdata("END ProcessControl::sendDatabldc1 dataset",dataset);

    datacomfirm=(DataRequestConfirm *)data;
    //PostThreadMessage(main_thread,PROCESS_TO_MAIN_THEAD,adress,dataset);
    Debug::getInstance()->debugdata("END ProcessControl::sendDataSensor2");
}
void ProcessControl::sendDataRequetsJostick(int lparam, int hparam, void * pointer, void *data){
    DWORD adress=(DWORD)pointer;
    DWORD dataset=(DWORD)data;
    DataRequestConfirm *datacomfirm=(DataRequestConfirm *)data;
    DataCommand *dataget=(DataCommand *)pointer;
    Debug::getInstance()->debugdata("START ProcessControl::sendDataRequetsJostick");
    if(lparam==VALUE_OK_INVALID){
        datacomfirm->ID=SENDTOSPI_CONTROLJOYSTICK;
        datacomfirm->crc=datacomfirm->ID+(unsigned char)(datacomfirm->Data>>16)
            +(unsigned char)(datacomfirm->Data>>8)+(unsigned char)(datacomfirm->Data)
            +(unsigned char)(datacomfirm->Request>>16)+(unsigned char)(datacomfirm->Request>>8)
            +(unsigned char)(datacomfirm->Request);
    }
    Debug::getInstance()->debugdata("END ProcessControl::sendDatabldc1 dataget command",(int)dataget);
    Debug::getInstance()->debugdata("END ProcessControl::sendDatabldc1 adress",adress);
    Debug::getInstance()->debugdata("END ProcessControl::sendDatabldc1 dataset",dataset);

    datacomfirm=(DataRequestConfirm *)data;
    //PostThreadMessage(main_thread,PROCESS_TO_MAIN_THEAD,adress,dataset);
    Debug::getInstance()->debugdata("END ProcessControl::sendDataRequetsJostick");
}
void ProcessControl::timeOut_5ms(int hparam, int lparam, void *head, void *content) {

}
void ProcessControl::timeOut_20ms(int lparam, int hparam, void * pointer, void *data) {

        // stopProcess( lparam,  hparam, pointer, data);
}





