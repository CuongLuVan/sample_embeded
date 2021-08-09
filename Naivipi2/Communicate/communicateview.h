
#pragma once
#include <iostream>


class CommunicateView {
public:
    static CommunicateView* getInstance() {
        if (INSTANCEDATA == NULL) {
            INSTANCEDATA = new CommunicateView();
        }
        return INSTANCEDATA;
        /*return (!INSTANCEDATA) ?
        INSTANCEDATA = new Common :
        INSTANCEDATA;*/
    }
public:
    void checkCommunicate(int lparam, int hparam, void * pointer, void *data);
    void warningCommunicate(int lparam, int hparam, void * pointer, void *data);
    void sendDataCommunicate(int lparam, int hparam, void * pointer, void *data);

    CommunicateView();
    ~CommunicateView();
    static CommunicateView *INSTANCEDATA;
};

