#include<unistd.h>
#include<stdio.h>
#include<signal.h>
#include<sys/time.h>
#include <signal.h>
#include<sys/wait.h>

void sys_err(const char*str){
    perror(str);
    exit(1);
}

void catch_child(int signo){    //有子进程终止，发送SIGGCHLD信号时，该函数会被内核回调
    pid_t wpid;
    int status;
    // while((wpid=wait(NULL))!=-1){
    //     printf("----------catch child id %d\n",wpid);//使用wait的方式
    // }
    while((wpid=waitpid(-1,&status,0))!=-1){//-1表示回收当前所有子进程，0表示堵塞
    if(WIFEXITED(status))       //WIFEXITED (status) 这个宏用来指出子进程是否为正常退出的，如果是，它会返回一个非零值
        printf("----------catch child id %d,ret=%d\n",wpid,WEXITSTATUS(status));//使用waitpid
    }
}

int main(int argc,char*argv[]){
    pid_t pid;
//阻塞！！！
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set,SIGCHLD);//阻塞信号
    sigprocmask(SIG_BLOCK,&set,NULL);//设置阻塞，屏蔽set设置的信号

    int i;
    for(i=0;i<15;i++)
        if((pid=fork())==0)
            break;

    if(15==i){
        struct sigaction act;
        act.sa_handler=catch_child;//将函数的地址传递
        sigemptyset(&act.sa_mask);//父进程注册信号捕捉函数
        act.sa_flags=0;

        sigaction(SIGCHLD,&act,NULL);//注册信号,SIGCHLD信号是子进程终止的时候产生
//解除阻塞！！！
        sigprocmask(SIG_UNBLOCK,&set,NULL);

        printf("I'm parent,pid= %d\n",getpid());
        sleep(1);//这个很重要，让父进程不先退出
    }else{
        printf("I'm child pid =%d\n",getpid());
        return i;//子进程结束
    }
}
//阻塞线程退出的信号是为了防止父进程还没注册成功，子进程就都死了，就没办法回收