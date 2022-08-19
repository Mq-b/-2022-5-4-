#include"wrap.h"

#define MAXLINE 80
#define SERV_PORT 9999

int main(int argc, char *argv[]){
	struct sockaddr_in servaddr;
	char buf[MAXLINE];
	int sockfd, n;

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));//初始化0
	servaddr.sin_family = AF_INET;//基本固定
	inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);//IP
	servaddr.sin_port = htons(SERV_PORT);//端口

	Connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));//连接

	while (fgets(buf, MAXLINE, stdin) != NULL) {
		Write(sockfd, buf, strlen(buf));//写到客户端
		n = Read(sockfd, buf, MAXLINE);
		if (n == 0) {
			printf("the other side has been closed.\n");//服务器停止接收的时候
			break;
		} else
			Write(STDOUT_FILENO, buf, n);//写到当前终端上
	}
	Close(sockfd);
}