#include<iostream>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>

using namespace std;

int main(){
    pid_t pid = fork();
    if(pid < 0){
        cout << "fork error:" << endl;
        exit(1);
    }
    if(pid == 0){
        cout << "first child pid: " << getpid() << ",ppid: " << getppid() << endl;
        sleep(5);
        cout << "second child pid: " << getpid() << ",ppid: " << getppid() << endl;
        int a = 100;
        while(1){
            wait(&a);
            cout << a << endl;
        }
        return 0;
    }

    sleep(1);
    cout << "parent pid: " << getpid() << ",ppid: " << getppid() << endl;
    cout << "I am die ..." << endl;
    return  0;
}