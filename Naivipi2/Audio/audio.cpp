
#include "Audio/audio.h"
#include "Audio/audiomodel.h"
//#include "debug.h"
#include "define_audio.h"
//#include "stdafx.h"
#include <iostream>


#pragma comment(lib, "winmm.lib")

using namespace std;

Audio::Audio() {

}

Audio::~Audio() {

}

void Audio::defaultVolume(int lparam, int hparam, void * pointer, void *data) {

    //Debug::getInstance()->debugdata("END Audio::warningAudio");

}
void Audio::sendDataToAudio(int lparam, int hparam, void * pointer, void *data) {
    //Debug::getInstance()->debugdata("START Audio::sendataToAudio");


    //Debug::getInstance()->debugdata("END Audio::sendataToAudio");
}

void Audio::warningAudio(int lpadam, int hpadam, void * pointer, void *data) {
    //Debug::getInstance()->debugdata("START Audio::warningAudio");

    switch (lpadam == 1) {
    case H_ENUM_HANGED_BUTTONSENSOR :
        cout << "thong bao Nut dieu khien cam bien bi treo \n";
    case H_ENUM_IMPEDIMENT:
        cout << "thong bao Dam phai chuong ngai vat \n";
    case H_ENUM_OUT_IMPACT:
        cout << "thong bao Bi do xe do tac dong ben ngoai \n";
//    case H_ENUM_STAIR_SLIDE:
  //      cout << "thong bao Truot cau thang \n";
    case H_ENUM_HOLE:
        cout << "thong bao Ho ga \n";
    case M_ENUM_DOWNGRADE:
        cout << "thong bao Xe xuong doc \n";
    case M_ENUM_POTHOLE:
        cout << "thong bao nguoi O ga \n";
    case M_ENUM_USER_STROKE:
        cout << "thong bao Nguoi su dung bi ngat, dot quy,... \n";
 //   case M_ENUM_MCU_HANG:
  //      cout << "thong bao Vi dieu khien bi treo \n";
    case L_ENUM_DRAGED_SENSOR:
        cout << "thong bao Cam bien bi troi \n";
    case L_ENUM_SPIN_AROUND:
        cout << "thong bao Xe quay tron do loi cam bien \n";
    case L_ENUM_BUMPY_WAY:
        cout << "thong bao Duong soc \n";
    case H_SLAVE_CHECK_HALL:
        cout << "thong bao Check_Hall \n";
    case H_SLAVE_RUN_MOTOR:
        cout << "thong bao Run_Motor \n";
//    case H_SLAVE_OVER_CURRENT:
 //       cout << "thong bao Over_Current \n";
    case H_SLAVE_DIRECTION:
        cout << "thong bao Direction \n";
  //  case M_SLAVE_HANGED_SENSOR:
  //      cout << "thong bao Vi dieu khien bi treo \n";
    case M_SLAVE_OVER_TEMPERATURE:
        cout << "thong bao Qua nhiet  \n";
 //   case L_SLAVE_UNDERSTAND:
 //       cout << "thong bao Understand  \n";
    case H_SENSORS_SPIN_AROUND:
        cout << "thong bao Xe quay tron do loi cam bien \n";
    case H_SENSORS_IMPEDIMENT:
        cout << "thong bao Dam phai chuong ngai vat \n";
    case H_SENSORS_OUT_IMPACT:
        cout << "thong bao Bi do xe do tac dong ben ngoai \n";
    case H_SENSORS_HOLE:
        cout << "thong bao Ho ga  \n";
    case H_SENSORS_ZICZAG:
        cout << "thong bao Xe lang lach \n";
    case M_SENSORS_HANGED_MCU:
        cout << "thong bao Vi dieu khien bi treo  \n";
 //   case M_SENSORS_POTHOLE:
  //      cout << "thong bao O ga \n";
    case M_SENSORS_DOWNGRADE:
        cout << "thong bao Xe xuong doc  \n";
    case M_SENSORS_MPU6050_ERROR:
        cout << "thong bao Cam bien MPU6050 hong  \n";
    case L_SENSORS_SENSOR_ERROR:
        cout << "thong bao ca bien khac hong \n";
    case L_SENSORS_OVER_SAFETEMP:
        cout << "thong bao > nhiet do an toan \n";
    case L_SENSORS_HUMIDITY:
        cout << "thong bao do am ? 1 :0 \n";
    case L_SENSORS_PRESSURE:
        cout << "thong bao ap luc ? 1 : 0 \n";
    case L_SENSORS_LIGHT:
        cout << "thong bao anh sang ? 1 : 0 \n";
    case L_SENSORS_SUPERSONIC_L:
        cout << "thong bao sieu am L ? 1 : 0 \n";
    case L_SENSORS_SUPERSONIC_R:
        cout << "thong bao sieu am R ? 1 : 0 \n";
    }
  //S  Debug::getInstance()->debugdata("END Audio::warningAudio");

}

