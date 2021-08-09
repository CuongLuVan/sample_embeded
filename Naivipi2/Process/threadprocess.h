#ifndef THREADPROCESS_H
#define THREADPROCESS_H

#include <QThread>
#include <QMutex>
#include <QDebug>
#include <QTimer>

class ThreadProcess : public QThread
{
    Q_OBJECT
public:
     ThreadProcess(QObject *parent = 0);
     ~ThreadProcess();
    void run();
    void setDataThreadProcess(int lparam,int hparam, void * pointer, void *data);
signals:
    void resultReadyThreadProcess(int lparam,int hparam, void * pointer, void *data);
public slots:
    void resultReadyThreadProcessTimeout();
private:
    bool flag_receive = false;
    int mlparam;
    int mhparam;
    void * mpointer;
    void *mdata;

public:
    bool flag_exit = true;


};

#endif // THREADPROCESS_H
