#include<unistd.h>
#include<stdio.h>
#include<signal.h>
#include<sys/time.h>
#include <signal.h>
#include<stdbool.h>

void sys_err(const char*str){
    perror(str);
    exit(1);
}

void sig_cath(int signo){
    if(signo==SIGINT){
        printf("catch you!! %d\n",signo);//Ctrl+C
        sleep(5);//在5秒之中重复按下ctrl+c依然只会执行一次打印
    }
    else if(signo==SIGQUIT)
        printf("-----------catch you!! %d\n",signo);//Ctrl+\
        
}

int main(){
    struct sigaction act,oldact;
    act.sa_handler=sig_cath;        //设置捕捉函数
    sigemptyset(&act.sa_mask);      //初始化
    sigaddset(&act.sa_mask,SIGQUIT);//指定在act的信号执行中，SIGQUIT信号被阻塞,也就是说默认在执行act信号的捕捉函数过程中是可以执行别的信号
    act.sa_flags=0;                 //设置默认处理动作

    int ret=sigaction(SIGINT,&act,&oldact);//注册信号，第三个参数其实没什么用目前，只是为了传出参数，但是我们目前不需要
    if(ret==-1){
        sys_err("sigaction error");
    }
    ret=sigaction(SIGQUIT,&act,&oldact);//再注册一个信号

    while(true);
}
/*信号捕捉特性：

	1. 捕捉函数执行期间，信号屏蔽字 由 mask --> sa_mask , 捕捉函数执行结束。 恢复回mask

	2. 捕捉函数执行期间，本信号自动被屏蔽(sa_flgs = 0).            //27行

    3.	捕捉函数执行期间，被屏蔽信号多次发送，解除屏蔽后只处理一次！*///16行


//信号的调用原理就是用户态和内核态来回切