#include "threadprocess.h"
#include "processcontrol.h"
ProcessControl *ProcessControl::INSTANCEDATA = NULL;

ThreadProcess::ThreadProcess(QObject *parent)
    : QThread(parent)
{

}
ThreadProcess::~ThreadProcess(){

}

void ThreadProcess::run()
{
    qDebug()<<"Thread Process";
    while(flag_exit){

        if(flag_receive){
           // qDebug()<<"Emited to Process";
          // emit resultReadyThreadProcess(mlparam,mhparam,mpointer,mdata);
           ProcessControl::getInstance()->execute(mlparam,mhparam,mpointer,mdata);
           flag_receive = false;
        }
    }
}

void ThreadProcess::setDataThreadProcess(int lparam, int hparam, void *pointer, void *data)
{
    mdata = data;
    mpointer = pointer;
    mhparam = hparam;
    mlparam = lparam;
    flag_receive = true;
}

void ThreadProcess::resultReadyThreadProcessTimeout(){
    ProcessControl::getInstance()->sendTimeout20ms(1,mhparam,mpointer,mdata);
}
