#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char * const envp[] = {"AA=11", "BB=22", NULL};
    printf("Entering main ...\n");
    int ret;
    //ret =execl("./hello", "hello", NULL);//直接运行hello可执行文件
    execle("./hello", "/home/guiguli/cpp_c/c进程/hello", NULL, envp);//第一个参数是执行的命令，第二个参数是路径，第三个参数是可变，不需要，第四个参数是传递参数给hello
    if(ret == -1)
        perror("execl error");
    printf("Exiting main ...\n");
    return 0;
}
/*int execle(const char *path, const char *arg, ..., char *const envp[]);*/
/*如果执行excle的话就会打印
Entering main ...
hello pid=22468
hello: AA=11
hello: BB=22
*/
//excle相当于自定义环境变量
//exec系列函数的主要功能就是替换当前进程运行的内容