#include "mainaction.h"
#include "define_thread.h"
MainAction::MainAction()
{
}
MainAction::~MainAction()
{
    delete threadAudioControl;
    delete threadCommunicateControl;
    delete threadProcessControl;
    delete threadScreenControl;
}
void MainAction::start(){
    threadAudioControl = new ThreadAudio();
    threadCommunicateControl = new ThreadCommunicate();
    threadProcessControl = new ThreadProcess();
    threadScreenControl = new ThreadScreen();

    QObject::connect(threadAudioControl,SIGNAL(resultReadyThreadAudio(int, int, void *, void *)),this,SLOT(handleResultsAudio(int,int,void*,void*)));
    QObject::connect(threadProcessControl,SIGNAL(resultReadyThreadProcess(int, int, void *, void *)),this,SLOT(handleResultsProcess(int,int,void*,void*)));
    QObject::connect(threadCommunicateControl,SIGNAL(resultReadyThreadCommunicate(int, int, void *, void *)),this,SLOT(handleResultsCommunicate(int,int,void*,void*)));
    QObject::connect(threadScreenControl,SIGNAL(resultReadyThreadScreen(int, int, void *, void *)),this,SLOT(handleResultsScreen(int,int,void*,void*)));

    threadAudioControl->start();
    threadCommunicateControl->start();
    threadProcessControl->start();
    threadScreenControl->start();
    timer = new QTimer(this);
    timer->setInterval(TIMEOUT_20MS);
    connect(timer,SIGNAL(timeout()), threadProcessControl, SLOT(resultReadyThreadProcessTimeout()));
    timer->start();
}

int MainAction::getLparam(int lparam)
{
    return lparam;
}

int MainAction::getHparam(int hparam)
{
    return hparam;
}


void MainAction::handleResultsAudio(int lparam,int hparam, void * pointer, void *data){


    qDebug() <<"handleResultsAudio";

    //threadCommunicateControl->setDataThreadCommunicate(lparam,hparam,pointer,data);
    //threadProcessControl->setDataThreadProcess(lparam,hparam,pointer,data);
    //threadScreenControl->setDataThreadScreen(lparam,hparam,pointer,data);
}

void MainAction::handleResultsCommunicate(int lparam,int hparam, void * pointer, void *data){

    qDebug() <<"handleResultsCommunicate";
    //threadAudioControl->setDataThreadAudio(lparam,hparam,pointer,data);
    //threadProcessControl->setDataThreadProcess(lparam,hparam,pointer,data);
    //threadScreenControl->setDataThreadScreen(lparam,hparam,pointer,data);
}

void MainAction::handleResultsProcess(int lparam,int hparam, void * pointer, void *data){
    qDebug() <<"handleResultsProcess";
    //threadAudioControl->setDataThreadAudio(lparam,hparam,pointer,data);
    //threadCommunicateControl->setDataThreadCommunicate(lparam,hparam,pointer,data);
    //threadScreenControl->setDataThreadScreen(lparam,hparam,pointer,data);

}

void MainAction::handleResultsScreen(int lparam,int hparam, void * pointer, void *data){

    qDebug() <<"handleResultsScreen";

    //threadAudioControl->setDataThreadAudio(lparam,hparam,pointer,data);
    //threadCommunicateControl->setDataThreadCommunicate(lparam,hparam,pointer,data);
    //threadProcessControl->setDataThreadProcess(lparam,hparam,pointer,data);
}

