#include<stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{

     pid_t id=fork();
     if(id==0)//当前子进程
     {
          printf("child start!\n");
          sleep(1);
          execl("/bin/ls","-a","-l","-n","-i",NULL);//第一个参数是路径，后面是可变参数，我们需要一个NULL表示结束
          printf("child end!\n");    
     }
     else
     {
          pid_t ret=wait(NULL);//回收子进程
          if(ret>0)
          {
               printf("wait child success!\n");
          }
     }
     return 0;
}
/*1、使用execl：
带有字母l(表⽰示list)的exec函数要求将新程序的每个命令行参数都当作一个参数传给 它,命令行 参数的个数是可变的,因此函数原型中有…,…中的最后⼀一个可变参数应该是 NULL, 起sentinel的作用
int execl(const char *path, const char *arg, ...);*/