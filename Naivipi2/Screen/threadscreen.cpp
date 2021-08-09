#include "threadscreen.h"
#include "screencontrol.h"
ScreenControl *ScreenControl::INSTANCEDATA = NULL;

ThreadScreen::ThreadScreen(QObject *parent)
    : QThread(parent)
{

}
ThreadScreen::~ThreadScreen(){

}

void ThreadScreen::run()
{
     qDebug()<<"Thread Screen";
     while(flag_exit)
     {
      if(flag_receive)
        {
          //qDebug() << " Emited to Screen";
            //emit resultReadyThreadScreen(mlparam,mhparam,mpointer,mdata);
          ScreenControl::getInstance()->execute(mlparam,mhparam,mpointer,mdata);
          flag_receive = false;
        }
     }
}

void ThreadScreen::setDataThreadScreen(int lparam, int hparam, void *pointer, void *data)
{
    mdata = data;
    mpointer = pointer;
    mhparam = hparam;
    mlparam = lparam;
    flag_receive = true;
}
