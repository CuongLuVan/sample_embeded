#include "threadcommunicate.h"

#include <Communicate/communicatecontrol.h>
CommunicateControl *CommunicateControl::INSTANCEDATA = NULL;


ThreadCommunicate::ThreadCommunicate(QObject *parent)
    : QThread(parent)
{

}
ThreadCommunicate::~ThreadCommunicate(){

}

void ThreadCommunicate::run()
{
    qDebug()<<"Thread Communicate";
    while(flag_exit){

        if(flag_receive){
            //qDebug()<<"Emited to Communicate";
          // emit resultReadyThreadCommunicate(mlparam,mhparam,mpointer,mdata);
            CommunicateControl::getInstance()->execute(mlparam,mhparam,mpointer,mdata);
            flag_receive = false;
        }
    }
}

void ThreadCommunicate::setTimer()
{
}

void ThreadCommunicate::setDataThreadCommunicate(int lparam, int hparam, void *pointer, void *data)
{
    mdata = data;
    mpointer = pointer;
    mhparam = hparam;
    mlparam = lparam;
    flag_receive = true;
}
