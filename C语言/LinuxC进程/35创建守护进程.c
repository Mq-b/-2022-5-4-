#include<unistd.h>
#include<stdio.h>
#include<signal.h>
#include<sys/time.h>
#include <signal.h>
#include<sys/wait.h>
#include<sys/stat.h>

void sys_err(const char*str){
    perror(str);
    exit(1);
}

int main(int argc,char*argv[]){
    pid_t pid;
    int ret,fd;

    pid=fork();
    if(pid>0)
        exit(0);                //父进程终止

    pid=setsid();               //创建新会话
    if(pid==-1)
        sys_err("setsid error");

    ret=chdir("/home/guiguli/");    //改变工作目录位置
    if(ret==-1)
        sys_err("chdir error");

    umask(0022);                            //改变文件访问权限掩码

    close(STDIN_FILENO);//关闭标准输入设备
    fd=open("/dev/null");
    if(fd==-1)
        sys_err("open error");

    dup2(fd,STDOUT_FILENO);//重定向标准输出(stdout)
    dup2(fd,STDERR_FILENO);//重定向标准错误输出(stderr)

    while(1);                   //模拟 守护进程业务
}