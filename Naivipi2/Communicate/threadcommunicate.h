#ifndef THREADCOMMUNICATE_H
#define THREADCOMMUNICATE_H

#include <QThread>
#include <QMutex>
#include <QDebug>
#include <QTimer>

class ThreadCommunicate : public QThread
{
    Q_OBJECT
public:
     ThreadCommunicate(QObject *parent = 0);
     ~ThreadCommunicate();
    void run();
    void setTimer();
    void setDataThreadCommunicate(int lparam,int hparam, void * pointer, void *data);
signals:
    void resultReadyThreadCommunicate(int lparam,int hparam, void * pointer, void *data);
private:
    bool flag_receive = false;
    int mlparam;
    int mhparam;
    void * mpointer;
    void *mdata;

public:
     bool flag_exit = true;

};

#endif // THREADCOMMUNICATE_H
