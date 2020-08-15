#include<iostream>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
using namespace std;

int main(){
    int msgid = msgget(0x123456, 0);
    if(msgid < 0){
        perror("creat msg queue fail");
        return -1;
    }else
        cout << "open msg success ..." << endl;
    int ret;
    char buf[1024] = {0};
    ret = msgrcv(msgid, buf, 15, 0, 0);
    if(ret < 0){
        cout << "recv msg fail" << endl;
        return -2;
    }else
        cout << "ret: " << ret << " buffer: " << buf << endl;
}