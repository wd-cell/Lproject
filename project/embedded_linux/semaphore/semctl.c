#include<stdio.h>
#include<linux/sem.h>
#define NUMS 10;

int get_sem_val(int sid, int semnum){ //取得当前信号量
    return semctl(sid, semnum, GETVAL, 0);
}
int main(){
    int i;
    int semid;
    int pid,ret;
    struct sembuf sem_op; //信号集结构
    union semun sem_val; //信号量数值

    semid = semget(IPC_PRIVATE,1 , IPC_CREAT | 0600); //建立有一个信号的信号量集
    //private私有，只有本用户使用，若为正整数，则为公共的。1为信号集的数量
    if(semid < 0){
        perror("creat sem error");
        exit(1);
    }
    printf("creat %d sem success\n", semid);

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
            printf("%d 使用者： %d \n", i, get_sem_val(semid, 0));
        }
    }else{ //父进程,制造者
        for(i=0; i< 10; ++i){
            sem_op.sem_num = 0;
            sem_op.sem_op = 1;
            sem_op.sem_flg = 0;
            semop(semid, &sem_op, 1); //操作信号量，每次+1
            printf("%d 制造者： %d \n", i, get_sem_val(semid, 0));
        }
    }
    exit(0);
}