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
    int ret,i;
    pid_t pid;

    ret=pipe(fd);//创建管道
    if(ret==-1)
    {
        sys_err("pipe error");
    }
    
    for(i=0;i<2;i++){//创建两个进程
        pid=fork();
        if(pid==-1)
            sys_err("fork error");
        if(pid==0)
            break;
    }

    if(i==2){//父进程
        close(fd[0]);
        close(fd[1]);
        wait(NULL);//父进程一定后结束
        wait(NULL);
    }else if(i==0){
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);//重定向标准输出设备为管道(写)
        execlp("ls","ls",NULL);
    }else if(pid==0){
        close(fd[1]);
        dup2(fd[0],STDIN_FILENO);//重定向标准输入设备(读)
        execlp("wc","wc","-l",NULL);
    }
}
//本程序可以视作13的修改
//ulimit -a命令可以查看管道 栈大小等参数，单位是Kb，也就是栈区8MB， (512 bytes, -p) 8，管道也就是512*8也就是4096bytes，即为4kb