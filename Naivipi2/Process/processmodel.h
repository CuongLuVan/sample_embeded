
#include <iostream>
#include <mutex>
#include <QtGlobal>
#include <define_thread.h>
//#include <Define_Api.h>


class ProcessModel {
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

    static ProcessModel *INSTANCEDATA;
public:
    ProcessModel();
    ~ProcessModel();
    static ProcessModel* getInstance() {
        static ProcessModel *INSTANCEDATA;
        if(INSTANCEDATA == NULL) {
            INSTANCEDATA = new ProcessModel();
        }
        return INSTANCEDATA;
    }

    void sendRequest(int lparam, int hparam, void * pointer, void *data);
    void stopProcess(int lparam, int hparam, void * pointer, void *data);
    void readStatusBldc(int lparam, int hparam, void * pointer, void *data);
    void stopGas(int lparam, int hparam, void * pointer, void *data);
    void processDataBldc(int lparam, int hparam, void * pointer, void *data);
    void processDataSensor(int lparam, int hparam, void * pointer, void *data);
    void processData(int lparam, int hparam, void * pointer, void *data);
    void ProcessDataCommunicate(int lparam, int hparam, void * pointer, void *data);
    void processDataAudio(int lparam, int hparam, void * pointer, void *data);
    void processDataScreen(int lparam, int hparam, void * pointer, void *data);
    int checkWarning(int lparam, int hparam, void * pointer, void *data);
    void checkTypeData(int hparam,int lparam,void *head,void *content);
    void timeout(int hparam,int lparam,void *head,void *content);
    void setTimeout_20ms(int hparam,int lparam,void *head,void *content);
    void processDataJoyStick(int lparam, int hparam, void * pointer, void *data);
    void Process(int lparam, int hparam, void * pointer, void *data);
    bool checkSensor(int lparam, int hparam, void * pointer, void *data);
    bool checkJoystick(int lparam, int hparam, void * pointer, void *data);
    bool checkBldc(int lparam, int hparam, void * pointer, void *data);
    int classifyWarning(int lparam, int hparam, void *pointer, void *data);
    void processWarningDataBldc(int lparam, int hparam, void * pointer, void *data);
    void processWarningDataJoystick(int lparam, int hparam, void * pointer, void *data);
    void processWarningDataSensor(int lparam, int hparam, void * pointer, void *data);
    HighLevelIncident *wh_from_sensor,*wh_from_slave,*wh_from_joystick;
        MediumLevelIncident *wm_from_sensor,*wm_from_slave,*wm_from_joystick;
        LowLevelIncident   *wl_from_sensor,*wl_from_slave,*wl_from_joystick;
};


