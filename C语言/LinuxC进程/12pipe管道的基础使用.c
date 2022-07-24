#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void sys_err(const char*str){
    perror(str);
    exit(1);
}

int main(int argc,char*argv[])
{
    int ret;
    int fd[2];
    pid_t pid;

    const char*str="hello pipe\n";
    char buf[1024];

    ret=pipe(fd);
    if(ret==-1)
        sys_err("pipe error");

    pid=fork();
    if(pid>0){
        close(fd[0]);//父进程关闭读端
        write(fd[1],str,strlen(str));//数据写入到管道
        sleep(1);//防止主进程先退出
        close(fd[1]);
    }else if(pid==0){
        close(fd[1]);//子进程关闭写端
        ret=read(fd[0],buf,sizeof(buf));//读取父进程写入到管道的数据
        write(STDOUT_FILENO,buf,ret);//将读取到的数据显示到终端
        close(fd[0]);
    }
}
//管道只能单向流动，也就是一方写，一方读