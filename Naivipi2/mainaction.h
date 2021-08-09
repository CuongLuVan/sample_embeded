#ifndef MAINACTION_H
#define MAINACTION_H
#include <QObject>
#include <QApplication>
#include <QDebug>
#include "Audio/threadaudio.h"
#include "Communicate/threadcommunicate.h"
#include "Process/threadprocess.h"
#include "Screen/threadscreen.h"
#include <QTimer>

class MainAction : public QObject
{
    Q_OBJECT
public:
    MainAction();
    ~MainAction();

    void start();
    int getLparam(int lparam);
    int getHparam(int hparam);

public slots:
    void handleResultsAudio(int lparam,int hparam, void * pointer, void *data);
    void handleResultsScreen(int lparam,int hparam, void * pointer, void *data);
    void handleResultsCommunicate(int lparam,int hparam, void * pointer, void *data);
    void handleResultsProcess(int lparam,int hparam, void * pointer, void *data);
private :
    ThreadAudio *threadAudioControl;
    ThreadCommunicate *threadCommunicateControl;
    ThreadProcess *threadProcessControl;
    ThreadScreen *threadScreenControl;
    QTimer *timer;
};

#endif // MAINACTION_H
