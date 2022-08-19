#include"wrap.h"

#define SRV_PORT 9999

void catch_child(int signum){
    while(waitpid(0,NULL,WNOHANG)>0);
}

int main(int argc,char*argv[]){
    int lfd,cfd;
    pid_t pid;
    int ret,i;
    struct sockaddr_in srv_addr,clt_addr;
    char buf[BUFSIZ];
    socklen_t clt_addr_len;
    //memset(&srv_addr,0,sizeof(srv_addr));
    bzero(&srv_addr,sizeof(srv_addr));//将地址结构清零，和上面的效果一样

    srv_addr.sin_family=AF_INET;
    srv_addr.sin_port=htons(SRV_PORT);
    srv_addr.sin_addr.s_addr=htonl(INADDR_ANY);

    lfd=Socket(AF_INET,SOCK_STREAM,0);

    Bind(lfd,(struct sockaddr*)&srv_addr,sizeof(srv_addr));

    Listen(lfd,128);

    while(1){
        cfd=Accept(lfd,(struct sockaddr*)&clt_addr,&clt_addr_len);
        pid=fork();
        if(pid<0){
            perr_exit("fork error");
        }else if(pid==0){
            close(lfd);
            break;
        }else{//主线程，处理进程回收
            struct sigaction act;
            act.sa_handler=catch_child;//设置信号的处理函数
            sigemptyset(&act.sa_mask);//清空信号级
            act.sa_flags=0;//默认0即可

            sigaction(SIGCHLD,&act,NULL);//注册信号,SIGCHLD信号是子进程终止的时候产生
            if(ret!=0){
                perr_exit("sigaction error");
            }
            close(cfd);
        }
    }
    if(pid==0){//子进程执行
        for(;;){
        ret=Read(cfd,buf,sizeof(buf));
        if(ret==0){
            close(cfd);
            exit(1);
        }
        for(i=0;i<ret;i++)
            buf[i]=toupper(buf[i]);
        write(cfd,buf,ret);//写到客户端
        write(STDOUT_FILENO,buf,ret);//写到当前终端
        }
    }
}