#include<iostream>
#include<sys/ipc.h>
#include<sys/msg.h>
using namespace std;

int main(){
    int msgid = msgget(0x123456, IPC_CREAT | 0777);
    if(msgid < 0){
        perror("msgget fail");
        return -1;
    }
    cout << "msgget success ..." << endl;
}