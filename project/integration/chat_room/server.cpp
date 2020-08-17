#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<string.h>
#include<thread>
#include<fcntl.h>
#include<unistd.h>
#include<sys/time.h>
#include<arpa/inet.h>
using namespace std;

#define MAXCONNECTION 40
#define msleep(x) (usleep(x*1000))

struct Data{ //客户端连入数据结构
    int live; //0无人用，1有人用
    int sockfd;
    in_addr in;
    unsigned short port;
};

Data arr[MAXCONNECTION] = {0};
void do_thread_showconnect();
void do_thread_clientopt(int i);

int main(){
    int sock = socket(AF_INET, SOCK_STREAM, 0); //创建套接字
    if(sock < 0){
        perror("get socket fail");
        return -1;
    }

    int on = 4; //设置端口复用
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int));

    sockaddr_in saddr; //服务器地址
    saddr.sin_family = AF_INET;
    saddr.sin_port = (htons(10086));
    saddr.sin_addr.s_addr = INADDR_ANY; //监听所有本机地址

    int ret = bind(sock, (sockaddr*)&saddr, sizeof(saddr));
    if(ret < 0){
        cout << "bind fail" << endl;
        return -2;
    }
    //监听连接
    listen(sock,30); //队列长度

    int peersockfd;
    sockaddr_in peeraddr;
    socklen_t len = sizeof(peeraddr);
    Data tmp;
    char* message = "too more connection";
    int i;
    thread tid(do_thread_showconnect); //创建线程显示已连接客户端个数
    tid.detach();

    while(1){
        peersockfd = accept(sock, (sockaddr*)&peeraddr, &len);
        if(peersockfd < 0){
            perror("accept fail");
            return -3;
        }
        tmp.sockfd = peersockfd;
        tmp.in = peeraddr.sin_addr;
        tmp.port = ntohs(peeraddr.sin_port);
        tmp.live = 1;

        for(i=0; i < MAXCONNECTION; ++i){ //入列
            if(arr[i].live == 0){
                arr[i] = tmp;
                break;
            }
        }

        if(i == MAXCONNECTION){ //判断是否已满
            write(peersockfd, message, strlen(message));
            close(peersockfd);
            continue;
        }
        
        thread tid2(do_thread_clientopt, i); //创建线程显示客户端之间互相发送的即时消息
        tid2.detach();
    }
    return 0;
}

void do_thread_showconnect(){
    int i, count = 0;
    while(1){
        system("clear");
        cout << "客户端连接信息： 连接人数： " << count << endl;
        count = 0;
        for(i = 0; i < MAXCONNECTION; ++i){
            if(arr[i].live == 1){
                count++;
                cout << "IP： " << inet_ntoa(arr[i].in) << " port: " << arr[i].port << endl;
            }
        }
        msleep(100); //每0.1秒刷新一次
    }
}

void do_thread_clientopt(int i){
    //转发信息
    int num = i;
    char buf[12240] = {0};
    char tmp[10240] = {0};
    int ret;
    timeval tv;
    struct timezone tz; //只能这种写法，原因未知
    tm* tt;
    int j;

    while(1){
        ret = read(arr[num].sockfd, tmp, 1024);
        if(ret <= 0) break;
        tmp[ret] = '\0';
        gettimeofday(&tv, &tz);
        tt = localtime(&tv.tv_sec);
        sprintf(buf, "%s @ %d: %d: %d: \n%s", inet_ntoa(arr[num].in), tt->tm_hour, tt->tm_min
        , tt->tm_sec, tmp);

        for(j = 0; j < MAXCONNECTION; ++j){ //发送数据到所有客户端，实现群聊效果
            if(arr[j].live == 1)
                write(arr[j].sockfd, buf, strlen(buf));
        }
    }
    close(arr[num].sockfd);
    arr[num].live = 0;
}