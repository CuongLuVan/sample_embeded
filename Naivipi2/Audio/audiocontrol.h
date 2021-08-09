
#include <iostream>
#include "define_thread.h"
class AudioControl {
public:
    static AudioControl* getInstance() {
        if (INSTANCEDATA == NULL) {
            INSTANCEDATA = new AudioControl();
        }
        return INSTANCEDATA;
        /*return (!INSTANCEDATA) ?
        INSTANCEDATA = new Common :
        INSTANCEDATA;*/
    }
public:
    void sendRequestAudio(int lparam, int hparam, void * pointer, void *data);
    void execute(int lparam, int hparam, void * pointer, void *data);
    void reSendRequestAudio(int lparam, int hparam, void * pointer, void *data);
    void Stop(int lparam, int hparam, void * pointer, void *data);
    AudioControl();
    ~AudioControl();
    static AudioControl *INSTANCEDATA;
    static DWORD main_thread;
};

