#include"wrap.h"
#define SERV_PORT 9527
void sys_err(const char*str){
    perror(str);
    exit(1);
}
int main(){
    int cfd;
    int conter=10;
    char buf[BUFSIZ];

    struct sockaddr_in serv_addr;  //服务器地址架构
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(SERV_PORT);

    inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr.s_addr);

    cfd=Socket(AF_INET,SOCK_STREAM,0);//使用封装的Socket则不用再检查返回值

    int ret=connect(cfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    if(ret!=0)
        sys_err("connect error");

    while(--conter){
        write(cfd,"hello\n",6);//发送给服务器
        ret=read(cfd,buf,sizeof(buf));//读取服务器发送的数据
        write(STDOUT_FILENO,buf,ret);//显示到屏幕
        sleep(1);
    }
    close(cfd);
}
//gcc 02client的实现.c 03错误处理函数封装\(wrap\).c  -o client