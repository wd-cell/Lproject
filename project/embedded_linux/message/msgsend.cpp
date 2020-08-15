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
    char* p = "hello msg queue";
    ret = msgsnd(msgid, p, strlen(p), 0);
    if(ret < 0){
        perror("send msg fail");
        return -2;
    }else
        cout << "send msg success ..." << endl;
}