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
#include<stdio.h>
using namespace std;

void do_thread(int i);
int main(){
    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if(sd < 0){
        perror("get socket fail");
        return -1;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(10086);
    addr.sin_addr.s_addr = inet_addr("192.168.2.115");

    int ret = connect(sd, (sockaddr *)&addr, sizeof(addr));
    if(ret != 0){
        perror("connect fail");
        return -3;
    }
    cout << "connect success ...\n";

    thread tid(do_thread, sd); //读取服务器发来的数据并显示
    tid.detach();

    char buf[1024] = {0};
    string stmp;
    while(1){
        //阻塞从标准输出读取信息到buf
        // ret = read(0, buf, 1024); //read会读入换行
        // if(ret > 1024)
        //     continue;

        // stmp.clear(); //linux下getline函数不一样
        // getline(cin, stmp);
        // strcpy(buf, stmp.c_str());

        // int n = 120;
        // getline(buf, &n, STDIN_FILENO);

        fgets(buf, 120, stdin); //也读入了换行
        if(strlen(buf) > 1024) continue;

        //按下回车后将buf中的内容写到文件描述符
        //通过服务器转发给其他正在连接的客户端
        write(sd, buf, strlen(buf)); //注意第三个参数最好是strlen(buf)形式
        // send(sd, buf, strlen(buf), 0);
    }
}

void do_thread(int i){
    int sd = i;
    int ret;
    char buf[1024] = {0};
    while(1){
        ret = recv(sd, buf, 1024, 0); //从服务器读取数据并显示
        if(ret <= 0)
            break;
        buf[ret] = '\0';
        cout << "recv:" << buf << endl;
    }
}