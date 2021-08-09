
#include <iostream>
#define  HRESULT int
class Audio {
public:
    static Audio* getInstance() {
        if (INSTANCEDATA == NULL) {
            INSTANCEDATA = new Audio();
        }
        return INSTANCEDATA;
        /*return (!INSTANCEDATA) ?
        INSTANCEDATA = new Audio :
        INSTANCEDATA;*/
    }
public:
    void defaultVolume(int lparam, int hparam, void * pointer, void *data);
    void warningAudio(int lparam, int hparam, void * pointer, void *data);
    void sendDataToAudio(int lparam, int hparam, void * pointer, void *data);

    Audio();
    ~Audio();
    static Audio *INSTANCEDATA;
};
//DataBaseMemorry* DataBaseMemorry::INSTANCEDATA = nullptr;
