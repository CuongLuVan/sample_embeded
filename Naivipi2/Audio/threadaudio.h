#ifndef THREADAUDIO_H
#define THREADAUDIO_H

#include <QThread>
#include <QMutex>
#include <QDebug>


class ThreadAudio : public QThread
{
    Q_OBJECT
public:
     ThreadAudio(QObject *parent = 0);
     ~ThreadAudio();
    void run();
    void setDataThreadAudio(int lparam,int hparam, void * pointer, void *data);
signals:
    void resultReadyThreadAudio(int lparam,int hparam, void * pointer, void *data);
private:
    bool flag_receive = false;
    int mlparam;
    int mhparam;
    void * mpointer;
    void *mdata;
public:
     bool flag_exit = true;

};

#endif // THREADAUDIO_H
