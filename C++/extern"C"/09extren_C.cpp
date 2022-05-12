#include<iostream>
#include<thread>
#include"C.h"
//如果是老代码，h文件没有写extern"C"那么可以使用下面这种方式
extern"C" {
#include"C.h"
}
int main() {
    std::thread threads(display);
    threads.join();
}