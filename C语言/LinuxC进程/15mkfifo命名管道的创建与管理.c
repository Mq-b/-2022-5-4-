#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>

void sys_err(const char*str){
    perror(str);
    exit(1);
}

int main(){
    int ret=mkfifo("mytestfifo",0664);//第一个参数是管道名称，可以在当前目录看到，第二个参数是权限
    if(ret==-1)
        sys_err("mkfifo error");
}