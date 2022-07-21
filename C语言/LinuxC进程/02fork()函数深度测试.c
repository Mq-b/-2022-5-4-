#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int n=0;
int main()
{
    printf("当前进程main = %u \n",getpid());
    pid_t pit;
    for(int i=0;i<4;i++)
    {
    pit=fork();
    if(pit==0)//这个判断非常重要，防止创建了子进程后，子进程继续在for里面创建进程
        break;
    if(pit==-1){
        puts("error");
        _exit(1);
        }   
    }

    if(pit!=0){//父进程
        n++;
        printf("当前是父进程 ID为= %u,n= %d\n",getegid(),n);
        usleep(100);//最好写上
        }
    if(pit==0){//子进程
        n++;
        printf("当前是子进程 ID= %u,对应父进程ID= %u, n= %d\n",getpid(),getppid(),n);
        }
}