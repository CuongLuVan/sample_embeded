
#include "audiomodel.h"
#include <iostream>
#include "debug.h"
#include "audio.h"
#pragma comment(lib, "winmm.lib")

//#pragma comment(lib, "winmm.lib")
using namespace std;
//Debug * debge::INSTANCEDATA = NULL;
//Debug *Debug::INSTANCEDATA=NULL;
AudioModel::AudioModel() {

}

AudioModel::~AudioModel() {

}

void AudioModel::getInitDataAudio(int lparam, int hparam, void * pointer, void *data) {
    Debug::getInstance()->debugdata("START AudioModel::getInitDataAudio");
    cout << "Chao mung den voi he thong cua chung toi " << endl;
    playAudioData(1, 0, NULL, NULL);
    Debug::getInstance()->debugdata("END AudioModel::getInitDataAudio");
}
void AudioModel::sendRequestAudio(int lparam, int hparam, void * pointer, void *data) {
    Debug::getInstance()->debugdata("START AudioModel::sendRequestAudio");
    if (lparam) {

        Audio::getInstance()->sendDataToAudio(1, 0, NULL, NULL);
    }
    Debug::getInstance()->debugdata("END AudioModel::sendRequestAudio");

}
void AudioModel::playAudioData(int padam1, int padam2, void * pointer, void *data) {
    if (padam1) {
        //PlaySound(TEXT("F:\\canhac\\tron\\Canh Hoa Roi - Lam Tam Nhu.mp3"), NULL, SND_FILENAME);
       // PlaySound(TEXT("HNNN.wav"), NULL, SND_FILENAME | SND_ASYNC);
        //PlaySoundW(TEXT("C:/t.wav"), NULL, SND_FILENAME); //GetLastError returns 0
    }


}

void AudioModel::playAudioData1(int padam11, int padam22, void * pointer1, void *data1) {
    cout << "bai hat 2!!!!!!!!!!!!!!!!!\n";
}
