
#include <iostream>
#include <QObject>
#include <QString>
#include <QTimer>
 class CommunicateModel :public QObject{
     Q_OBJECT
    public:
     static CommunicateModel* getInstance(){
          if(INSTANCEDATA == NULL){
              INSTANCEDATA = new CommunicateModel();
          }
          return INSTANCEDATA;
        /*return (!INSTANCEDATA) ?
            INSTANCEDATA = new Common :
            INSTANCEDATA;*/
    }
 public:
     void getInitDataCommunicate(int lparam, int hparam, void * pointer, void *data);
     void callFunCanTx(int lparam, int hparam, void * pointer, void *data);
     void CallDummy(int lparam, int hparam, void * pointer, void *data);
     void Communicate(int lparam, int hparam, void * pointer, void *data);
     void timeout(int lparam, int hparam, void * pointer, void *data);
     void sendTimeOut(int lparam, int hparam, void * pointer, void *data);
     void start(int lparam, int hparam, void * pointer, void *data);
     CommunicateModel();
     ~CommunicateModel();
     static CommunicateModel *INSTANCEDATA;
     QTimer *timer;
    // static counter_CommunicateDummy ;
};


