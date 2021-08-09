
#include "communicatemodel.h"
#include "debug.h"
#include <iostream>
#include <errno.h>
#include "define_thread.h"
#include <QObject>
#include <QString>
/*#include <wiringPiSPI.h>
#include <unistd.h>*/

int counter_CommunicateDummy=0;

CommunicateModel::CommunicateModel(){


}
CommunicateModel::~CommunicateModel(){


}

void CommunicateModel::Communicate(int lparam, int hparam, void * pointer, void *data){

}
void CommunicateModel::start(int lparam, int hparam, void * pointer, void *data){

}
void CommunicateModel::sendTimeOut(int lparam, int hparam, void * pointer, void *data){

}

void CommunicateModel::timeout(int lparam, int hparam, void * pointer, void *data){

}


void CommunicateModel::getInitDataCommunicate(int lparam, int hparam, void * pointer, void *data) {

     int fd, result;
   unsigned char buffer[100];
   /*
   cout << "Initializing" << endl ;

   // Configure the interface.
   // CHANNEL insicates chip select,
   // 500000 indicates bus speed.
   fd = wiringPiSPISetup(CHANNEL, 500000);

   cout << "Init result: " << fd << endl;

   // clear display
   buffer[0] = 0x76;
   wiringPiSPIDataRW(CHANNEL, buffer, 1);

*/


}


void CommunicateModel::callFunCanTx(int lparam, int hparam, void * pointer, void *data) {
    Debug::getInstance()->debugdata("START CommunicateModel::callfunCanTx  =>",lparam);


    Debug::getInstance()->debugdata("START CommunicateModel::callfunCanTx  =>",lparam);
         // The last character
      /*buffer[0] = 0x7e;
      buffer[1] = i;
      result = wiringPiSPIDataRW(CHANNEL, buffer, 2);
      */
}
void CommunicateModel::CallDummy(int lparam, int hparam, void * pointer, void *data){
    Debug::getInstance()->debugdata("START CommunicateModel::CallDummy  =>",lparam);

    counter_CommunicateDummy++;
    if(counter_CommunicateDummy>3){
        timer = new QTimer(this);
        timer->setInterval(TIMEOUT_20MS);
        connect(timer,SIGNAL(timeout()), this, SLOT(resultReadyThreadProcessTimeout()));
        timer->start();

    }
    Debug::getInstance()->debugdata("START CommunicateModel::callfunCanTx  =>",lparam);
}
