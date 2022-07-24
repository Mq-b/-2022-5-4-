#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/mman.h>
#include<sys/stat.h>
struct  student
{
    int  id;
    char  name[256];
    int  age;
};

void sys_err(const char*str){
    perror(str);
    exit(1);
}

int main(int argc,char*argv[]){
    struct student stu={10,"小明",18};
    struct student *p;
    int fd;

    fd=open("test_map",O_RDONLY);
    if(fd==-1){
        sys_err("open error");
    }


    p=mmap(NULL,sizeof(stu),PROT_READ,MAP_SHARED,fd,0);//读
    if(p==MAP_FAILED){
        sys_err("mmap error");
    }
    close(fd);
    while(1){
        printf("id= %d,name= %s,age= %d\n",p->id,p->name,p->age);
        sleep(1);
    }

    munmap(p,sizeof(stu));
}