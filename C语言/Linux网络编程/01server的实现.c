#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<ctype.h>

#define SERV_PORT 9527

void sys_err(const char*str){
    perror(str);
    exit(1);
}

int main(){
    int lfd=0,cfd;
    char buf[BUFSIZ];
    int ret=0;
    struct sockaddr_in serv_addr,clit_addr;//创建结构体并初始化
    socklen_t clit_addr_len;

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(SERV_PORT);
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);

    lfd=socket(AF_INET,SOCK_STREAM,0);//第一个参数表示使用IPv4地址，tcp或udp协议，第二个参数表示使用tcp协议，0表示默认协议。返回指向新创建的socket的文件描述符，和文件操作差不多
    if(lfd==-1){
        sys_err("socket error");
    }

    bind(lfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));//bind()的作用是将参数1和addr绑定在一起，使sockfd这个用于网络通讯的文件描述符监听addr所描述的地址和端口号

    listen(lfd,128);//listen()函数用于服务器，使已绑定的socket等待监听客户端的连接请求，并设置服务器同时可连接的数量，第二个参数就是数量

    clit_addr_len=sizeof(clit_addr);
    cfd=accept(lfd,(struct sockaddr*)&clit_addr,&clit_addr_len);//三方握手完成后，服务器调用accept()接受连接
    if(cfd==-1){
        sys_err("accept error");
    }
    while(1){
    ret=read(cfd,buf,sizeof(buf));
    write(STDOUT_FILENO,buf,ret);//先将读取到的输出到屏幕一下

    for(int i=0;i<ret;i++)
        buf[i]=toupper(buf[i]);//转换为大写
    
    write(cfd,buf,ret);//然后写入客户端中
    }   
}
//我们可以偷懒一下，用终端模拟客户端:nc 127.0.0.1 9527      nc是一个命令 然后127.0.0.1表示本机IP 9527表示端口号
//然后就能输入数据了

//accept函数
/*addr是一个传出参数，accept()返回时传出客户端的地址和端口号。addrlen参数是一个传入传出参数（value-result argument），传入的是调用者提供的缓冲区addr的长度以避免缓冲区溢出问题，
传出的是客户端地址结构体的实际长度（有可能没有占满调用者提供的缓冲区）。如果给addr参数传NULL，表示不关心客户端的地址。*/