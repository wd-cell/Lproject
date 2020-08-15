//cpp未成功
#include<iostream>
#include<linux/sem.h>
#include<sys/sem.h>
#include<unistd.h>
#define NUMS 10;
using namespace std;
int get_sem_val(int sid, int semnum){ //取得当前信号量
    return semctl(sid, semnum, GETVAL, 0);
}
int main(){
    int i;
    int semid;
    int pid,ret;
    struct sembuf sem_op; //信号集结构
    union semun sem_val; //信号量数值

    semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600); //建立有一个信号的信号量集
    if(semid < 0){
        cout << "creat sem error" << endl;
        exit(1);
    }
    cout << "creat " << semid << " sem success" << endl ;

    sem_val.val = 1; //信号量初始化
    ret = semctl(semid, 0, SETVAL, sem_val); //设置信号量，0为第一个信号量，1为第二个...
    if(ret < 0){
        perror("initialize sem error");
        exit(1);
    }

    pid = fork();
    if(pid < 0){
        perror("fork error");
        exit(1);
    }
    else if(pid == 0){ //子进程，使用者
        for(i=0; i< 10; ++i){
            sem_op.sem_num = 0;
            sem_op.sem_op = -1;
            sem_op.sem_flg = 0;
            semop(semid, &sem_op, 1); //操作信号量，每次-1
            cout << i << " 使用者: " << get_sem_val(semid, 0) << endl;
        }
    }else{ //父进程,制造者
        for(i=0; i< 10; ++i){
            sem_op.sem_num = 0;
            sem_op.sem_op = 1;
            sem_op.sem_flg = 0;
            semop(semid, &sem_op, 1); //操作信号量，每次+1
            cout << i << " 制造者: " << get_sem_val(semid, 0) << endl;
        }
    }
    exit(0);
}