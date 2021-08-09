
#include <iostream>

 class Common{
    public:
     static Common* getInstance(){
          if(INSTANCEDATA == NULL){
              INSTANCEDATA = new Common();
          }
          return INSTANCEDATA;
    }
 public:
     Common();
     ~Common();


     static Common *INSTANCEDATA;
};

//void CALLBACK timer20msCallBack(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime);
void registerIntrerrupHMI(int lparam, int hparam, void * pointer, void *data);
