
#include "screenControl.h"
#include "screenHMI.h"
#include "screenModel.h"
#include "debug.h"
#include "define_thread.h"

ScreenHMI *ScreenHMI::INSTANCEDATA=NULL;
DWORD ScreenControl::main_thread=0;

ScreenControl::ScreenControl() {

}

ScreenControl::~ScreenControl() {

}

void ScreenControl::execute(int lparam, int hparam, void * pointer, void *data){
    DWORD *datapointer;
    Debug::getInstance()->debugdata("START ScreenControl::execuse");
    if(lparam==1){
        if(hparam==MAIN_THEAD){
            datapointer=(DWORD *)(data);
            main_thread=*datapointer;
            ScreenHMI::getInstance()->drawScreenHMI(lparam,hparam,pointer,data);
        }
        else
        if(hparam==FROM_PROCESS_TASK)
        {
            Debug::getInstance()->debugdata("START ScreenControl::FROM_PROCESS_TASK");
        }
        else
        if(hparam==FROM_AUDIO_TASK)
        {

        }
        else
        if(hparam==FROM_COMMUNICATE_TASK)
        {

        }
    }
    Debug::getInstance()->debugdata("END ScreenControl::execuse");
}

void ScreenControl::getInitDataScreen(int lparam, int hparam, void * pointer, void *data){

}
void ScreenControl::sendRequestScreen(int lparam, int hparam, void * pointer, void *data) {

}
void ScreenControl::sendDataToScreen(int lparam, int hparam, void * pointer, void *data) {

}
void ScreenControl::reSendRequestScreen(int lparam, int hparam, void * pointer, void *data) {

}
void ScreenControl::stopScreen(int lparam, int hparam, void * pointer, void *data) {

}
void ScreenControl::callFunCheck(int lparam, int hparam, void * pointer, void *data) {

}
