#include<iostream>
#include<unistd.h> //unix标准文件
int main()
{
    pid_t pid;
    std::cout<<"parent have!"<<std::endl;
        pid = fork();//执行fork的时候到底发生了什么?
    if(pid == -1)//错误创建
    {
        perror("fork error");
            _exit(1);
    }
    else if(pid == 0)//子进程
    {
        std::cout<<"i am child,pid = "<<getpid()<<" my parent is:"<<getppid()<<std::endl;//getpid()方法会获取当前获取ID，getppid()获取当前进程父进程ID
    }
    else//父进程
    {
        std::cout<<"i am parent,pid = "<<getpid()<<" my parent is:"<<getppid()<<std::endl;//打印的两个结果一样，因为父进程只有一个
    }
    std::cin.get();
}