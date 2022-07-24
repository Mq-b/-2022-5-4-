#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{

     pid_t id=fork();
     if(id==0)
     {
          printf("child start!\n");
          sleep(1);
          const char*_argv[]={"-a","-l","-n","-i",NULL};
          execvp("ls",_argv);//只需要命令与参数
          printf("child end!\n");    
     }
     else
     {
          pid_t ret=wait(NULL);
          if(ret>0)
          {
               printf("wait child success!\n");
          }
     }
     return 0;
}