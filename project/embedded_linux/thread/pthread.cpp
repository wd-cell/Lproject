//C的写法，不太可行
#include<iostream>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
using namespace std;

void* thread_fun1(void *arg){ //C的写法
    int n = *((int*) arg);
    cout << "thread one : " << n << endl;
}
void* thread_fun2(void *arg){
    int n = *((int*) arg);
    cout << "thread two : " << n << endl;
}
int main(){
    int ret = 0;
    pthread_t pid = 0;
    pthread_t pid2 = 0;
    int num = 100;
    int* ptr = &num;

    ret = pthread_create(&pid, NULL, thread_fun1, (void*)ptr);
    if(ret < 0){
        perror("pthreat_create fail");
        exit(EXIT_FAILURE);
    }
    pthread_join(pid, NULL);

    num = 200;
    ret = pthread_create(&pid2, NULL, thread_fun2, (void*)ptr);
    if(ret < 0){
        perror("pthreat_create fail");
        exit(EXIT_FAILURE);
    }
    
    pthread_join(pid2, NULL);
}