//windows下Cpp的写法，linux同样可行，编译需加 -lpthread

// #include<unistd.h>
// #include<pthread.h>

#include<iostream>
#include<thread>
using namespace std;

void output(int n){
    cout << "thread: " << n << endl;
}
int main(){
    for(int i=0; i<6; ++i){
        thread t(output, i);
        t.join();
    }
}