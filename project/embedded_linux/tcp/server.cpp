#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<unistd.h>
using namespace std;

int main(){
    int ret;
    int sock = socket(AF_INET, SOCK_STREAM, 0); //创建套接字
    sockaddr_in saddr; //服务器地址
    saddr.sin_family = AF_INET;
    saddr.sin_port = (htons(8000));
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //指定本地地址

    ret = bind(sock, (sockaddr*)&saddr, sizeof(saddr));
    if(ret < 0){
        cout << "bind fail" << endl;
        exit(1);
    }
    //监听连接
    listen(sock,5); //队列长度
    sockaddr_in cli;
    int len = sizeof(cli);

    int socklis = accept(sock, (sockaddr*)&cli, (socklen_t*)&len); //建立连接
    char buf[20] = {0};
    recv(socklis, buf, 20, 0);
    cout << "buf is " << buf << endl;
    close(sock);
    close(socklis);
}