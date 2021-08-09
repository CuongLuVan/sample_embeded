#include "common.h"
#include "debug.h"


//ProcessModel *ProcessModel::INSTANCEDATA=NULL;

Common::Common(){

}

Common::~Common(){

}
/*
void CALLBACK timer20msCallBack(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime){
    Debug::getInstance()->debugdata("START timer20msCallBack");
    ProcessControl::getInstance()->sendTimeout20ms(5,20,NULL,NULL);
    Debug::getInstance()->debugdata("END timer20msCallBack");
}*/

void registerIntrerrupHMI(int lparam, int hparam, void * pointer, void *data){

}
