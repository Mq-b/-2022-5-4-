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
    int fd,len;
    char buf[4096];

    if(argc<2){
        printf("./a.out fifoname\n");
        return -1;
    }
    fd=open(argv[1],O_RDONLY);
    if(fd<0)
        sys_err("open");
    while(1){
        len=read(fd,buf,sizeof(buf));//一直读
        write(STDOUT_FILENO,buf,len);//写到屏幕上
        sleep(1);
    }
    close(fd);
}
//我们是和16配合着使用，16和17都没有创建mkfifo命名管道，因为15已经创建了。
//我们需要先将16和17编译 gcc 16mkfifo无关系的进程通信\(写\).c -o  fifo_w
//                    gcc 17mkfifo读.c -o fifo_r
//然后在运行的时候使用先前创建的管道 ./fifo_w mytestfifo
//                              ./fifo_r mytestfifo
//这样就行了