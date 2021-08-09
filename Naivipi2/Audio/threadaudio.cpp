#include "threadaudio.h"
#include "audiocontrol.h"

AudioControl *AudioControl::INSTANCEDATA=NULL;
ThreadAudio::ThreadAudio(QObject *parent)
    : QThread(parent)
{


}
ThreadAudio::~ThreadAudio(){

}

void ThreadAudio::run()
{
     qDebug()<<"Thread Audio";
     while(flag_exit){
         if(flag_receive){
            // qDebug()<<"Emited to Audio";
           // emit resultReadyThreadAudio(mlparam,mhparam,mpointer,mdata);
            AudioControl::getInstance()->execute(mlparam,mhparam,mpointer,mdata);
            flag_receive = false;
         }
     }
}



void ThreadAudio::setDataThreadAudio(int lparam, int hparam, void *pointer, void *data)
{
    mdata = data;
    mpointer = pointer;
    mhparam = hparam;
    mlparam = lparam;
    flag_receive = true;
}
