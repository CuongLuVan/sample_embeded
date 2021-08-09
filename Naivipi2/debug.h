
#include <iostream>
#include "stdlib.h"


class Debug {
public:
    static Debug* getInstance() {
        static Debug *INSTANCEDATA;
        if (INSTANCEDATA == NULL) {
            INSTANCEDATA = new Debug();
        }
        return INSTANCEDATA;
        /*return (!INSTANCEDATA) ?
        INSTANCEDATA = new INSTANCEDATA :
        INSTANCEDATA;*/
    }
public:
    Debug();
    ~Debug();
    void debugdata(char *data);
    void debugdata(char *type,int data);
    void debug(char type,int data,int data1);

};

