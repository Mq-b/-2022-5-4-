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
          execlp("ls","-a","-l","-n","-i",NULL);//不需要指明路径
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
/*int execlp(const char *ﬁle, const char *arg, ...);*/