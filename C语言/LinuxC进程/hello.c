#include <unistd.h>
#include <stdio.h>
extern char** environ;

int main(void)
{
    printf("hello pid=%d\n", getpid());
    int i;
    for (i=0; environ[i]!=NULL; ++i)
    {
        printf("hello: %s\n", environ[i]);
    }
    return 0;
}
/*LinuxC中environ变量是一个char** 类型，存储着系统的环境变量。
如果直接运行或者调用的话就会，此段代码就会打印全部的环境变量*/
//如果像08文件那样调用，则会向environ传递参数，不再打印环境变量