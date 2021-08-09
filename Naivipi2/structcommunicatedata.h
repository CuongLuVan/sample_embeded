#ifndef STRUCTCOMMUNICATEDATA_H
#define STRUCTCOMMUNICATEDATA_H

#endif // STRUCTCOMMUNICATEDATA_H
#include "iostream"
#define SENDTOSPI_CONTROLBLDC1 1
#define SENDTOSPI_CONTROLBLDC2 2
#define SENDTOSPI_CONTROLSENSOR1 3
#define SENDTOSPI_CONTROLSENSOR2 4
#define SENDTOSPI_CONTROLJOYSTICK 5
#define MAX_CONTROL_DEVICE 6

#define VALUE_OK_INVALID  1
#define START_CONTROL  1
#define START_CONTROL_CHANGE_VALUE  1
#define  JOYSTICK_COMMUNICATE_COMMAND 0x51
#define AUDIO_COMMAND 0x52
#define SCREEN_DIRECT_COMMAND 0x53
#define  JOYSTICK_MECHANIC_COMMUNICATE_COMMAND 0x61
#define  JOYSTICK_MECHANIC_COMMUNICATE_COMMAND_F1 0x62

#define GROUP_WARNING_HIGHT  1
#define GROUP_WARNING_MEDIUM 2
#define GROUP_WARNING_LOW    3

#define NOMAL_FROM_JOYSTICK 1
#define NOMAL_FROM_SLAVE 2
#define NOMAL_FROM_SENSOR 3
#define NOMAL_FROM_AUDIO_TASK 4
#define NOMAL_FROM_SCREEN_TASK 5

#define WARNING_FROM_JOYSTICK 1
#define WARNING_FROM_SLAVE    2
#define WARNING_FROM_SENSOR   3
#define WARNING_FROM_AUDIO_TASK 4
#define WARNING_FROM_SCREEN_TASK 5
#define NO_WARNING 0
#define TimeOut 20
struct DataRequestConfirm
{
    unsigned char ID;
    unsigned int Data;
    unsigned int Request;
    unsigned char crc;
};
struct DataCommand
{
    int ID;
    int content;
    int detailcontent;
    int adresscommand;// DWORD
};

struct DataJoyStick
{
    int x;
    int y;
    bool enable;
    int warning;
};

struct DataBLDC
{
    long leng;
    double vehicleCurent;
    double vehicleControl;
    int lengt;
    int warning;
};
struct DataAudio
{
    double volume;
    double warning;

};
struct DataScreen
{
    double warning;
    double color;
};

struct DataSensor
{
    double distanceL; // left
    double distanceR; // right
    double distanceF; // front
    double distanceB; // behind

    int sensor_temp;        //nhiet do
    bool sensor_humi;       //do am
    bool sensor_pressure;  //ap suat
    bool sensor_light;    //anh sang

    double value_acceleration;

    int warning;
};
struct HighLevelIncident   // su co muc cao
{
 int code_incident;
 int address;
 bool warning;
};

struct MediumLevelIncident   // su co muc cao
{
 int code_incident;
 int address;
 bool warning;
};

struct LowLevelIncident   // su co muc cao
{
 int code_incident;
 int address;
 bool warning;
};



