#include<iostream>
#include<vector>
using namespace std;

void testHello(){
    vector<int> v = {1,2,3};
    for(int i : v)
        cout << i << " " ;
    cout << endl << "hello c11" << endl;
}

int main(){
    testHello();
}