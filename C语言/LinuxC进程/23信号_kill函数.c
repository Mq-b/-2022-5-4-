#include<unistd.h>
#include<signal.h>//提供信号的宏
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/mman.h>
#include<sys/stat.h>

void sys_err(const char*str){
    perror(str);
    exit(1);
}

int main(int argc,char*argv[]){
    pid_t pid=fork();
    if(pid>0){
        printf("parent,pid= %d,所在进程组=%d\n",getpid(),getpgrp());
        while(1);//父进程不能退出
    }else if(pid==0){
        printf("child pid=%d,ppid=%d,所在进程组=%d\n",getpid(),getppid(),getpgrp());
        sleep(2);
        kill(getppid(),SIGKILL);//kill函数使用方式和普通的kill命令没有区别，就是传递一个进程ID与信号
        kill(0,SIGKILL);//0表示删除调用kill函数的进程所在同一组的所有进程
    }
}
/*int kill（pid_t pid, int signum）

	参数：
		pid: 	> 0:发送信号给指定进程

			= 0：发送信号给跟调用kill函数的那个进程处于同一进程组的进程。

			< -1: 取绝对值，发送信号给该绝对值所对应的进程组的所有组员。

			= -1：发送信号给，有权限发送的所有进程。

		signum：待发送的信号

	返回值：
		成功： 0

		失败： -1 errno
*/
//每一个进程只有一个组