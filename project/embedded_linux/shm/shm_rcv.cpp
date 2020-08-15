#include<iostream>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include<signal.h>
#include<fcntl.h>
#include<stdlib.h>
using namespace std;

#define SHM_SIZE 1024

int main(){
    int shmid;
    char *shmptr;
    shmid = shmget(0x66, SHM_SIZE, IPC_CREAT | 0666);
    if(shmid < 0){
        perror("shmget fail");
        return -1;
    }
    shmptr = (char*) shmat(shmid, 0, 0);
    if(shmptr == (void*) -1){
        perror("shmat fail");
        return -2;
    }

    cout << shmptr << endl;
    shmdt(shmptr);
}