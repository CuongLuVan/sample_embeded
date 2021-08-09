
#include <iostream>


class ScreenModel {
public:
    static ScreenModel* getInstance() {
        if (INSTANCEDATA == NULL) {
            INSTANCEDATA = new ScreenModel();
        }
        return INSTANCEDATA;
        /*return (!INSTANCEDATA) ?
        INSTANCEDATA = new INSTANCEDATA :
        INSTANCEDATA;*/
    }
public:
    void getInitData(int lparam, int hparam, void * pointer, void *data);
    void sendRequestScreen(int lparam, int hparam, void * pointer, void *data);
    void reSendRequestScreen(int lparam, int hparam, void * pointer, void *data);
    void stopCommandScreen(int lparam, int hparam, void * pointer, void *data);
    void callFunCan(int lparam, int hparam, void * pointer, void *data);

    ScreenModel();
    ~ScreenModel();
    static ScreenModel *INSTANCEDATA;
};

