#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/mman.h>
#include<sys/stat.h>

int var=100;

void sys_err(const char*str){
    perror(str);
    exit(1);
}

int main(void){
    int *p;
    pid_t pid;
    int fd;
    fd=open("temp",O_RDWR | O_CREAT | O_TRUNC ,0644);
    if(fd<0){
        sys_err("open error");
    }
    ftruncate(fd,4);//设置文件大小

    p=(int*)mmap(NULL,4,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);//建立映射区,私有的
    if(p==MAP_FAILED){
        sys_err("mmap error");
    }
    close(fd);      //映射区建立完毕，即可关闭文件

    pid=fork();     //创建子进程
    if(pid==0){
        *p=2000;    //写共享内存
        var=1000;
        printf("子进程:child,*p=%d,var=%d\n",*p,var);
    }else{
        sleep(1);
        printf("父进程:child,*p=%d,var=%d\n",*p,var);
        wait(NULL);//等待子进程结束
        unlink("temp");//删除文件
        int ret=munmap(p,4);    //释放映射区
        if(ret==-1){
            sys_err("munmap error");
        }
    }
}