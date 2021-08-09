#include "audiocontrol.h"
#include "audio.h"
#include "debug.h"
#include "audiomodel.h"
#include "define_thread.h"

AudioModel *AudioModel::INSTANCEDATA = NULL;
Audio *Audio::INSTANCEDATA = NULL;
DWORD AudioControl::main_thread = 0;

AudioControl::AudioControl() {

}

AudioControl::~AudioControl() {

}

void AudioControl::execute(int lparam, int hparam, void * pointer, void *data) {
    DWORD *datapointer;
    Debug::getInstance()->debugdata("START AudioControl::execuse");
    if (lparam == 1) {
        if (hparam == MAIN_THEAD) {
            datapointer = (DWORD *)(data);
            main_thread = *datapointer;

            Debug::getInstance()->debugdata("START AudioControl::execuse==2");
            AudioModel::getInstance()->getInitDataAudio(lparam, hparam, pointer, data);
            Audio::getInstance()->defaultVolume(lparam, hparam, pointer, data);
            //Audio::getInstance()->wanningAudio(lparam, hparam, pointer, data);
            //AudioModel::getInstance()->sendRequestAudio(lparam,hparam,pointer,data);
            Debug::getInstance()->debugdata("END AudioControl::execuse==2");
        }
        else
            if (hparam == FROM_PROCESS_TASK)
            {
                Debug::getInstance()->debugdata("START AudioControl::FROM_PROCESS_TASK");

                AudioModel::getInstance()->playAudioData1(lparam, hparam, pointer, data);
                Audio::getInstance()->defaultVolume(lparam, hparam, pointer, data);
               // Audio::getInstance()->wanningAudio(lparam, hparam, pointer, data);

                Debug::getInstance()->debugdata("END AudioControl::FROM_PROCESS_TASK");

            }
            else
                if (hparam == FROM_COMMUNICATE_TASK)
                {
                    //AudioModel::getInstance()->playAudioData2(lparam,hparam,pointer,data);
                    //Audio::getInstance()->defaultVolume(lparam,hparam,pointer,data);
                    //Audio::getInstance()->wanningAudio(lparam,hparam,pointer,data);
                }
                else
                    if (hparam == FROM_SCREEN_TASK)
                    {
                        //AudioModel::getInstance()->playAudioData3(lparam,hparam,pointer,data);
                        //Audio::getInstance()->defaultVolume(lparam,hparam,pointer,data);
                        //Audio::getInstance()->wanningAudio(lparam,hparam,pointer,data);
                    }
    }
    Debug::getInstance()->debugdata("END AudioControl::execuse");
}

void AudioControl::sendRequestAudio(int lparam, int hparam, void * pointer, void *data) {

}
void AudioControl::reSendRequestAudio(int lparam, int hparam, void * pointer, void *data) {
}
