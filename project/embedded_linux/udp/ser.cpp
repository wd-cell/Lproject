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

    int loop = 1; //设置了recvfrom函数的超时机制，当loop设定的时间没有数据来到时，recvfrom会返回0
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &loop, sizeof(loop));
    int s = bind(sock, (sockaddr*)&saddr, sizeof(saddr));
    if(s < 0)
        perror("bind error");
    char buf[20] = {0};
    sockaddr_in caddr;
    int len = sizeof(caddr);
    recvfrom(sock, buf, 20, 0, (sockaddr*)&caddr, (socklen_t*)&len);
    cout << "buf is " << buf << endl;
    close(sock);
}