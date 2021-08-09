
#include "Communicate/communicatecontrol.h"
#include "debug.h"
#include "define_thread.h"
#include "structcommunicatedata.h"
#include "Communicate/communicatemodel.h"

CommunicateModel *CommunicateModel::INSTANCEDATA=NULL;
DWORD CommunicateControl::main_thread=0;
CommunicateControl::CommunicateControl() {

}

CommunicateControl::~CommunicateControl() {

}

void CommunicateControl::execute(int lparam, int hparam, void * pointer, void *data){
    DWORD *datapointer;
    DWORD dataf;
    DataRequestConfirm *datacomfirm=(DataRequestConfirm *)data;
    DataCommand *datacommand=(DataCommand *)pointer;

    Debug::getInstance()->debugdata("START CommunicateControl::execuse");
    if(lparam==VALUE_OK_INVALID){
        datapointer=(DWORD *)(data);
        if(hparam==MAIN_THEAD){
            main_thread=*datapointer;
        }
        else
        if(hparam==FROM_PROCESS_TASK)
        {
            /*

            ProcessModel::HighLevelIncident *dataCommandToProcess = (ProcessModel::HighLevelIncident *)data;
                        ProcessModel *point_data_PM = (ProcessModel *)pointer;

                        if(point_data_PM->checkWarning(lparam,hparam,pointer,data) == 1)
                        {

                        }

                        if(point_data_PM->checkWarning(lparam,hparam,pointer,data) == 0)
                        {
                            point_data_PM->classifyWarning(lparam,hparam,pointer,data);

                            // Solution for Joystick
                            if(point_data_PM->hCheck_Joystick.code_incident == 1){
                                Debug::getInstance()->debugdata("Solution hWarning joystick 1");
                            }
                            if(point_data_PM->hCheck_Joystick.code_incident == 2){
                                Debug::getInstance()->debugdata("Solution hWarning joystick 2");
                            }
                            if(point_data_PM->hCheck_Joystick.code_incident == 3){
                                Debug::getInstance()->debugdata("Solution hWarning joystick 3");
                            }
                            if(point_data_PM->hCheck_Joystick.code_incident == 4){
                                Debug::getInstance()->debugdata("Solution hWarning joystick 4");
                            }
                            if(point_data_PM->hCheck_Joystick.code_incident == 5){
                                Debug::getInstance()->debugdata("Solution hWarning joystick 5");
                            }

                            // Solution for slave
                            if(point_data_PM->hCheck_Slave.code_incident == 1){
                                Debug::getInstance()->debugdata("Solution hWarning Slave 1");
                            }
                            if(point_data_PM->hCheck_Slave.code_incident == 2){
                                Debug::getInstance()->debugdata("Solution hWarning Slave 2");
                            }
                            if(point_data_PM->hCheck_Slave.code_incident == 3){
                                Debug::getInstance()->debugdata("Solution hWarning Slave 3");
                            }
                            if(point_data_PM->hCheck_Slave.code_incident == 4){
                                Debug::getInstance()->debugdata("Solution hWarning Slave 4");
                            }

                            // Solution for Sensor
                            if(point_data_PM->hCheck_Sensor.code_incident == 1){
                                Debug::getInstance()->debugdata("Solution hWarning Sensor 1");
                            }
                            if(point_data_PM->hCheck_Sensor.code_incident == 2){
                                Debug::getInstance()->debugdata("Solution hWarning Sensor 2");
                            }
                            if(point_data_PM->hCheck_Sensor.code_incident == 3){
                                Debug::getInstance()->debugdata("Solution hWarning Sensor 3");
                            }
                            if(point_data_PM->hCheck_Sensor.code_incident == 4){
                                Debug::getInstance()->debugdata("Solution hWarning Sensor 4");
                            }
                            if(point_data_PM->hCheck_Sensor.code_incident == 5){
                                Debug::getInstance()->debugdata("Solution hWarning Sensor 5");
                            }
                            if(point_data_PM->hCheck_Sensor.code_incident == 6){
                                Debug::getInstance()->debugdata("Solution hWarning Sensor 6");
                            }

                        }*/
            /*if ((pointer != NULL) && (data != NULL)) {
                datapointer = (DWORD *)(pointer);
                dataf = *datapointer;
                datacommand = (DataCommand *)dataf;
                datapointer = (DWORD *)(data);
                dataf = *datapointer;
                datacomfirm = (DataRequestConfirm *)dataf;
                Debug::getInstance()->debugdata("START CommunicateControl::FROM_PROCESS_TASK content~~~~~~", datacommand->content);
                if (datacommand->ID == PROCESS_TO_MAIN_THEAD) {
                    if (datacommand->content<MAX_CONTROL_DEVICE) {
                        CommunicateModel::getInstance()->callfunCanTx(datacommand->content, datacommand->detailcontent, (void *)datacommand->adresscommand, (void *)datacomfirm);
                    }
                }
                DataRequestConfirm *datacomfirm = (DataRequestConfirm *)data;
                Debug::getInstance()->debugdata("END CommunicateControl::sendDatabldc1 datacomfirm->ID", datacomfirm->ID);
                Debug::getInstance()->debugdata("END CommunicateControl::sendDatabldc1 datacomfirm->ID", datacomfirm->Request);
            }*/
        }
        else
        if(hparam==FROM_AUDIO_TASK)
        {

        }
        else
        if(hparam==FROM_SCREEN_TASK)
        {

        }
    }
    Debug::getInstance()->debugdata("END CommunicateControl::execuse");
}

 void CommunicateControl::sendRequest(int lparam, int hparam, void * pointer, void *data) {

}
 void CommunicateControl::warningCommunicate(int lparam, int hparam, void * pointer, void *data) {

 }
