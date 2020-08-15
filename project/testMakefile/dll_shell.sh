#! /bin/bash

ls
g++ hello.cpp -shared -fPIC -o libhello.so
mv hello.cpp ../
ls
g++ test.cpp ./libhello.so -o test
ls
./test