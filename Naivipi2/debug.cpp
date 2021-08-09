
#include "debug.h"



using namespace std;
Debug::Debug() {

}

Debug::~Debug() {

}

void Debug::debugdata(char *type,int data){
    cout<<type<<data<<endl;
}

void Debug::debugdata(char *data){
    cout<<data<<endl;
}
