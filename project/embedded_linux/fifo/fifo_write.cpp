#include<iostream>
#include<string>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
using namespace std;

#define P_FIFO "txt"

int main(){
    char buf[20] = "hello write_fifo";
    int ret = 0;
    ret = mkfifo(P_FIFO, 0777);
    if(ret < 0){
        cout << "creat named pipe failed" << endl;
        return -1;
    }
    int fd;
    fd = open(P_FIFO,O_WRONLY);
    if(fd < 0){
        cout << "open failed." << endl;
        return -2;
    }
    write(fd, buf, sizeof(buf));
    close(fd);
    return 0;
}