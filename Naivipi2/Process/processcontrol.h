
#include <iostream>
#include "define_thread.h"

class ProcessControl {
public:
    struct HighLevelIncident   // su co muc cao
        {
         int code_incident;
         int address;
         bool warning;
        }hCheck_Joystick,hCheck_Slave,hCheck_Sensor;

        struct MediumLevelIncident   // su co muc trung binh
        {
         int code_incident;
         int address;
         bool warning;
        }mCheck_Joystick,mCheck_Slave,mCheck_Sensor;

        struct LowLevelIncident   // su co muc thap
        {
         int code_incident;
         int address;
         bool warning;
        }lCheck_Joystick,lCheck_Slave,lCheck_Sensor;

    static ProcessControl* getInstance() {

        if (INSTANCEDATA == NULL) {
            flag_control = 0;
            INSTANCEDATA = new ProcessControl();
        }
        return INSTANCEDATA;
        /*return (!INSTANCEDATA) ?
        INSTANCEDATA = new INSTANCEDATA :
        INSTANCEDATA;*/
    }
public:
    void execute(int lparam, int hparam, void * pointer, void *data);
    void sendTimeout20ms(int lparam, int hparam, void * pointer, void *data);
    void sendDatatoProcess(int lparam, int hparam, void * pointer, void *data);
    void reSendDatatoProcess(int lparam, int hparam, void * pointer, void *data);
    void stopProcess(int lparam, int hparam, void * pointer, void *data);
    void sendDatabldc1(int lparam, int hparam, void * pointer, void *data);
    void sendDatabldc2(int lparam, int hparam, void * pointer, void *data);
    void sendDataSensor1(int lparam, int hparam, void * pointer, void *data);
    void sendDataSensor2(int lparam, int hparam, void * pointer, void *data);
    void sendDataRequetsJostick(int lparam, int hparam, void * pointer, void *data);

    ProcessControl();
    ~ProcessControl();
    void timeOut_5ms(int hparam,int lparam,void *head,void *content);
    void timeOut_20ms(int hparam,int lparam,void *head,void *content);

    static ProcessControl *INSTANCEDATA;
    private:	static int flag_control;
                static DWORD main_thread;
                static DWORD Audio_thread;
                static DWORD Communicate_thread;
                static DWORD Screen_thread;
};

