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

int main(int argc,char*argv[]){
    int fd,i;
    char buf[4096];

    fd=open(argv[1],O_WRONLY);//以只写模式打开命名通道
    if(fd<0)
        sys_err("open");
    i=0;
    while(1){
        sprintf(buf,"hello itcast %d\n",i++);

        write(fd,buf,strlen(buf));
        sleep(1);
    }
    close(fd);
}