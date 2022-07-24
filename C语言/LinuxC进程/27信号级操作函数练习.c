#include<unistd.h>
#include<stdio.h>
#include<signal.h>
#include<sys/time.h>
#include <signal.h>

void sys_err(const char*str){
    perror(str);
    exit(1);
}

void print_set(sigset_t *set){
    for(int i=1;i<32;i++){
        if(sigismember(&set,i))//判断1是不是在set里面
            putchar('1');
        else
            putchar('0');
    }
    printf("\n");
}

int main(int argc,char*argv[]){
    sigset_t set,oldset,pedset;
    sigemptyset(&set);//清空信号级(也就是初始化而已)
    sigaddset(&set,SIGINT);//将Ctrl+C(停止)信号添加到集合中,可以添加多个信号，会屏蔽他们
    sigaddset(&set,SIGQUIT);
    sigaddset(&set,SIGBUS);

    int ret=sigprocmask(SIG_BLOCK,&set,&oldset);//SIG_BLOCK:设置阻塞，也就是设置屏蔽set的信号
    if(ret==-1){
        sys_err("sigprocmask error");
    }
    while(1){
    ret=sigpending(&pedset);//获取当前的pending信号，然后调用函数打印
    if(ret==-1){
        sys_err("sigprocmask error");
    }

    print_set(&pedset);
    sleep(1);
    }
}