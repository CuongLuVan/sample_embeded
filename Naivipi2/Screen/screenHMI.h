
#include <iostream>


class ScreenHMI {
public:
    static ScreenHMI* getInstance() {
        if (INSTANCEDATA == NULL) {
            INSTANCEDATA = new ScreenHMI();
        }
        return INSTANCEDATA;
        /*return (!INSTANCEDATA) ?
        INSTANCEDATA = new INSTANCEDATA :
        INSTANCEDATA;*/
    }
public:
    void drawScreenHMI(int lparam, int hparam, void * pointer, void *data);
    void warningScreen(int lparam, int hparam, void * pointer, void *data);
    void sendDataToScreen(int lparam, int hparam, void * pointer, void *data);
    ScreenHMI();
    ~ScreenHMI();
    static ScreenHMI *INSTANCEDATA;
};

