#include<unistd.h>
#include<fcntl.h>
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
    char*p=NULL;
    int fd;
    fd=open("testmap",O_RDWR | O_CREAT | O_TRUNC,0644);
    if(fd==-1)
        sys_err("open error");
/*
    lseek(fd,10,SEEK_END);      //这两个函数等价于ftruncate()函数
    write(fd,"\0",1);
*/
    ftruncate(fd,10);//扩展文件大小
    int len=lseek(fd,0,SEEK_END);//SEEK_END：读写偏移量将指向文件末尾 + 0 字节位置处，同样 0 可以为正、也可以为负，如果是正数表示往后偏移、如果是负数则表示往前偏移。
                                //返回值是当前读写位置

    p=mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(p==MAP_FAILED){
        sys_err("mmap error");
    }
    //使用p对文件进行读写操作
    strcpy(p,"hello mmap\n");     //写操作

    printf("------%s",p);

    int ret=munmap(p,len);//释放映射区
    if(ret==-1){
        sys_err("munmap error");
    }
}
