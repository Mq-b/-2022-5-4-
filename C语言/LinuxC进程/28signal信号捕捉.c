#include<unistd.h>
#include<stdio.h>
#include<signal.h>
#include<sys/time.h>
#include <signal.h>

void sys_err(const char*str){
    perror(str);
    exit(1);
}

void sig_cath(int signo){
    printf("catch you!! %d\n",signo);
}

int main(){
    signal(SIGINT,sig_cath);//注册信号捕捉函数,可以注册多个

    while (1){}
    
}