
#include <iostream>
#include "define_thread.h"
#include <Process/processcontrol.h>
#include <Process/processmodel.h>
class CommunicateControl {
public:
    static CommunicateControl* getInstance() {
        if (INSTANCEDATA == NULL) {
            INSTANCEDATA = new CommunicateControl();
        }
        return INSTANCEDATA;
        /*return (!INSTANCEDATA) ?
        INSTANCEDATA = new Common :
        INSTANCEDATA;*/
    }
public:
    void execute(int lparam, int hparam, void * pointer, void *data);
    void warningCommunicate(int lparam, int hparam, void * pointer, void *data);
    void sendRequest(int lparam, int hparam, void * pointer, void *data);
    void sendRequestCommunicate(int lparam, int hparam, void * pointer, void *data);

    CommunicateControl();
    ~CommunicateControl();
    static CommunicateControl *INSTANCEDATA;
private:
    static DWORD main_thread;
};

