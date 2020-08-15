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
#define MAX_USER 50
#define BUFSIZE 100
using namespace std;

int main(){
    int i = 0, j = 0;
    int sock = socket(AF_INET, SOCK_STREAM, 0); //创建套接字
    sockaddr_in saddr; //服务器地址
    saddr.sin_family = AF_INET; //IPv4
    saddr.sin_port = (htons(8000));
    saddr.sin_addr.s_addr = INADDR_ANY;

    int len = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &len, sizeof(len)); //设置socket选项
    int ret = bind(sock, (sockaddr*)&saddr, sizeof(saddr));
    if(ret < 0){
        cout << "bind fail" << endl;
        exit(1);
    }
    listen(sock, 5);
    pollfd fds[MAX_USER];
    for(i=0; i<MAX_USER; ++i){
        fds[i].fd = -1;
        fds[i].events = 0;
        fds[i].revents = 0;
    }
    fds[0].fd = sock;
    fds[0].events = POLLIN;
    fds[0].revents = 0;
    int count = 0;

    char buf[BUFSIZE] = {0};
    while(1){
        int ret = poll(fds, count+1, -1);
        for(i=0; i<count+1; ++i){
            if((fds[i].revents & POLLIN) && (fds[i].fd == sock)){ //监听服务器描述符，接受新连接
            // if(fds[0].revents & POLLIN){//按理和上句效果一样，但结果是可以建立新连接，却不能向其它连接输出
                sockaddr_in caddr;
                int len = sizeof(caddr);
                int fd = accept(sock, (sockaddr*)&caddr, (socklen_t*)&len);
                if(fd > 0)
                    cout << "client connect\n" ;
                else{
                    cout << "connect error\n";
                    continue;
                }
                count++;
                fds[count].fd = fd;
                fds[count].events = POLLIN | POLLRDHUP; //监听两个事件
                fds[count].revents = 0;
                cout << "client sum is " << count << endl;
            }else if(fds[i].revents & POLLRDHUP){ //监听挂起事件
                close(fds[i].fd);
                fds[i] = fds[count];
                count--;
                i--;
                cout << "client exit\n";
            }else if(fds[i].revents & POLLIN){ //监听是否有数据输入
                memset(buf, 0, BUFSIZE);
                int ret = read(fds[i].fd, buf, BUFSIZE);
                if(ret > 0){
                    for(j=1; j<count+1; ++j){ //将数据写入其他所有连接
                        if(fds[j].fd == fds[i].fd)
                            continue;
                        write(fds[j].fd, buf, ret);
                    }
                }
            }
        }
    }
    close(sock);
}