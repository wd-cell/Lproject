#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
using namespace std;

int main(){
    int sock = socket(AF_INET, SOCK_STREAM, 0); //创建套接字
    sockaddr_in saddr; //服务器地址
    saddr.sin_family = AF_INET;
    saddr.sin_port = (htons(8000));
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //指定本地地址

    connect(sock, (sockaddr*)&saddr, sizeof(saddr)); //建立连接
    char buf[20] = "hello socket\n";

    send(sock, buf, strlen(buf), 0); //发送数据
    close(sock);
}