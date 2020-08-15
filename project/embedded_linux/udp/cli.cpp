#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<unistd.h>
#include<netdb.h>
using namespace std;

int main(){
    int sock = socket(AF_INET, SOCK_DGRAM, 0); //创建套接字
    sockaddr_in saddr; //服务器地址
    saddr.sin_family = AF_INET;
    saddr.sin_port = (htons(8000));
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    char buf[20] = "udp sendto ok";
    sendto(sock, buf, 20, 0, (sockaddr*)&saddr, sizeof(saddr));
    close(sock);
}