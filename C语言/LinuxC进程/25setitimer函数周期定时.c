#include<unistd.h>
#include<stdio.h>
#include<signal.h>
#include<sys/time.h>
void myfunc(int signo){
    printf("hello word\n");
}
int main(){
    struct itimerval it,oldit;

    signal(SIGALRM,myfunc);//注册SIGALRW信号的捕捉处理函数

    it.it_value.tv_sec=2;//设置第一个闹钟两秒以后触发
    it.it_value.tv_usec=0;//微秒初始化

    it.it_interval.tv_sec=5;//设置第二个闹钟每五秒以后触发(周期定时)
    it.it_interval.tv_usec=0;//微秒初始化

    if(setitimer(ITIMER_REAL,&it,&oldit)==-1){
        perror("setitimer error");
        exit(-1);
    }

    while(1);
}

/*SIGALRM信号是操作系统中的其中一个信号。他的作用是设置进程隔多久后会收到一个SIGALRM信号。*/
/*第一次信息打印是两秒间隔，之后都是5秒间隔打印一次。可以理解为第一次是有个定时器，什么时候触发打印，之后就是间隔时间*/