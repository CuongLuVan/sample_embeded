
#include <iostream>
#include "define_thread.h"

class ScreenControl {
public:
    static ScreenControl* getInstance() {
        if (INSTANCEDATA == NULL) {
            INSTANCEDATA = new ScreenControl();
        }
        return INSTANCEDATA;
        /*return (!INSTANCEDATA) ?
        INSTANCEDATA = new INSTANCEDATA :
        INSTANCEDATA;*/
    }
public:
    void execute(int lparam, int hparam, void * pointer, void *data);
    void getInitDataScreen(int lparam, int hparam, void * pointer, void *data);
    void sendRequestScreen(int lparam, int hparam, void * pointer, void *data);
    void sendDataToScreen(int lparam, int hparam, void * pointer, void *data);
    void reSendRequestScreen(int lparam, int hparam, void * pointer, void *data);
    void stopScreen(int lparam, int hparam, void * pointer, void *data);
    void callFunCheck(int lparam, int hparam, void * pointer, void *data);
    ScreenControl();
    ~ScreenControl();
    static ScreenControl *INSTANCEDATA;
private:
    static DWORD main_thread;
};

