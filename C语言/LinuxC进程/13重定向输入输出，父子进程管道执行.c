#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void sys_err(const char*str){
    perror(str);
    exit(1);
}

int main()
{
    int fd[2];
    int ret;
    pid_t pid;

    ret=pipe(fd);
    if(ret==-1)
    {
        sys_err("pipe error");
    }
    pid=fork();
    if(pid==-1){
        sys_err("fork_error");
    }else if(pid>0){
        close(fd[1]);
        dup2(fd[0],STDIN_FILENO);//重定向标准输入设备(读)
        execlp("wc","wc","-l",NULL);
    }else if(pid==0){
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);//重定向标准输出设备为管道(写)
        execlp("ls","ls",NULL);
    }
}
//组合起来也就是ls | wc -l了