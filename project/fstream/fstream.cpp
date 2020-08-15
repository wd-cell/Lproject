#include<iostream>
#include<fstream>
using namespace std;

#define ADDRESS1 ("/home/wd/project/fstream/in2")
#define ADDRESS2 ("/home/wd/project/fstream/in.txt")

int main(){
    ifstream in(ADDRESS1, ios::in);
    ofstream out(ADDRESS2, ios::out);
    string s;
    // for(int i=0; i<3; ++i){
    //     getline(in,s);
    //     cout<<s<<endl;
    // }
    while(getline(in,s)){
        cout<<s<<endl;
        out<<s<<endl;
    }
    // cin>>s;
    in.close();
    out.close();
}