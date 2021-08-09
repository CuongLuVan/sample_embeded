
#include "screenModel.h"
#include "common.h"
#include "debug.h"
ScreenModel::ScreenModel() {

}

ScreenModel::~ScreenModel() {

}
void ScreenModel::getInitData(int lparam, int hparam, void * pointer, void *data) {
    Debug::getInstance()->debugdata("START ScreenModel::getInitData");
    registerIntrerrupHMI(lparam,hparam,pointer,data);
    Debug::getInstance()->debugdata("END ScreenModel::getInitData");
}
void  ScreenModel::sendRequestScreen(int lparam, int hparam, void * pointer, void *data) {

}
void ScreenModel::reSendRequestScreen(int lparam, int hparam, void * pointer, void *data) {

}
void ScreenModel::stopCommandScreen(int lparam, int hparam, void * pointer, void *data) {

}
void ScreenModel::callFunCan(int lparam, int hparam, void * pointer, void *data) {

}
