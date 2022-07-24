#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>

int main(int argc,char*argv[]){
    struct stat sbuf;
    int ret=stat(argv[1],&sbuf);//第一个参数是文件路径
    if(ret==-1){
        perror("stat error");
        exit(1);
    }
    printf("file size:%d\n",sbuf.st_size);//大小的单位是字节
    printf("file type:%d\n",sbuf.st_mode);
    printf("file permissions:%d\n",sbuf.st_mode);//权限
}