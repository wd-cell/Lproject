#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<unistd.h>
#include<poll.h>
#include<string.h>
#define __USE_GNU
using namespace std;

int main(){
    int sock = socket(AF_INET, SOCK_STREAM, 0); //创建套接字
    sockaddr_in saddr; //服务器地址
    saddr.sin_family = AF_INET;
    saddr.sin_port = (htons(8000));
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (sockaddr*)&saddr, sizeof(saddr));

    pollfd fds[2];
    fds[0].fd = 0; //STDIN_FILENO
    fds[0].events = POLLIN;
    fds[0].revents = 0;
    fds[1].fd = sock;
    fds[1].events = POLLIN | POLLRDHUP;
    fds[1].revents = 0;
    
    char rbuf[30] = {0};
    char buf[30] = {0};
    while(1){
        int ret = poll(fds, 2, -1); //无限等待，即挂起
        if(fds[0].revents & POLLIN){
            memset(rbuf, 0, 30);
            int ret = read(0, rbuf, sizeof(rbuf));
            write(sock, rbuf, ret);
            ret = 0;
        }
        if(fds[1].revents & POLLRDHUP){ //若服务器关闭
            cout << "server exit\n";
            break;
        }else if (fds[1].revents & POLLIN) //读取服务器发送数据，测试时开3个终端
        {
            memset(buf, 0, 30);
            int ret = read(sock, buf, sizeof(buf));
            write(STDOUT_FILENO, buf, ret);
            ret = 0;
        }
    }
    close(sock);
}