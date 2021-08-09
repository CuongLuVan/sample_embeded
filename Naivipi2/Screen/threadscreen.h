#ifndef THREADSCREEN_H
#define THREADSCREEN_H

#include <QThread>
#include <QMutex>
#include <QDebug>

class ThreadScreen : public QThread
{
    Q_OBJECT
public:
     ThreadScreen(QObject *parent = 0);
     ~ThreadScreen();
    void run();
    void setDataThreadScreen(int lparam,int hparam, void * pointer, void *data);
signals:
    void resultReadyThreadScreen(int lparam,int hparam, void * pointer, void *data);
private:
    bool flag_receive;
    int mlparam;
    int mhparam;
    void * mpointer;
    void *mdata;

public:
    bool flag_exit;

};

#endif // THREADSCREEN_H
