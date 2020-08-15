#include<iostream>
#include<string>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
using namespace std;

#define P_FIFO "txt"

int main(){
    int ret, fd;
    char buf[20];
    fd = open(P_FIFO,O_RDONLY);
    if(fd < 0){
        cout << "open fail" << endl;
        return -1;
    }
    while(1){
        memset(buf, 0, sizeof(buf));
        if(read(fd, buf, sizeof(buf)) == 0)
            cout << "no data" << endl;
        else{
            cout << "getdata: " << buf << endl ;
            break;
        }
    }
    close(fd);
    return 0;
}