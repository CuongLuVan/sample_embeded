
#include <iostream>


class AudioModel {
public:
    static AudioModel* getInstance() {
        if (INSTANCEDATA == NULL) {
            INSTANCEDATA = new AudioModel();
        }
        return INSTANCEDATA;
        /*return (!INSTANCEDATA) ?
        INSTANCEDATA = new Common :
        INSTANCEDATA;*/
    }
public:
    void getInitDataAudio(int lparam, int hparam, void * pointer, void *data);
    void reSendRequestAudio(int lparam, int hparam, void * pointer, void *data);
    void sendRequestAudio(int lparam, int hparam, void * pointer, void *data);
    void stopCommand(int lparam, int hparam, void * pointer, void *data);
    void playAudioData(int padam1, int padam2, void * pointer, void *data);
    void playAudioData1(int padam1, int padam2, void * pointer, void *data);
    AudioModel();
    ~AudioModel();
    static AudioModel *INSTANCEDATA;
};

