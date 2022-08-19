#include "wrap.h"
#define MAXLINE 80
#define SERV_PORT 9999

struct s_info {
	struct sockaddr_in cliaddr;
	int connfd;//文件描述符
};
void *do_work(void *arg)
{
	int n,i;
	struct s_info *ts = (struct s_info*)arg;//将传入线程的结构体转换
	char buf[MAXLINE];
	char str[INET_ADDRSTRLEN];
	
	while (1) {
		n = Read(ts->connfd, buf, MAXLINE);
		if (n == 0) {
			printf("the other side has been closed.\n");
			break;
		}
		printf("received from %s at PORT %d\n",inet_ntop(AF_INET, &(*ts).cliaddr.sin_addr, str, sizeof(str)),
            ntohs((*ts).cliaddr.sin_port));//打印IP与端口
		for (i = 0; i < n; i++)
			buf[i] = toupper(buf[i]);
		Write(ts->connfd, buf, n);//写到客户端
        Write(STDOUT_FILENO,buf,n);//写到自身终端
	}
	Close(ts->connfd);
}

int main(void){
	struct sockaddr_in servaddr, cliaddr;
	socklen_t cliaddr_len;
	int listenfd, connfd;
	int i = 0;
	pthread_t tid;
	struct s_info ts[256];

	listenfd = Socket(AF_INET, SOCK_STREAM, 0); //创建一个socket 得到一个lfd

	bzero(&servaddr, sizeof(servaddr));     //地址结构清零
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//推荐使用这个
	servaddr.sin_port = htons(SERV_PORT);

	Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));//绑定
	Listen(listenfd, 20);                                   //设置同一时刻链接服务器上限数

	printf("Accepting connections ...\n");
	while (1) {
		cliaddr_len = sizeof(cliaddr);
		connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);//阻塞监听客户端链接请求
		ts[i].cliaddr = cliaddr;//将Accept的传出参数传递给结构体
		ts[i].connfd = connfd;//文件描述符
		/* 达到线程最大数时，pthread_create出错处理, 增加服务器稳定性 */
		pthread_create(&tid, NULL, do_work, (void*)&ts[i]);
        pthread_detach(tid);                                    //子线程分离，防止僵尸线程产生
		i++;                                                
	}
	return 0;
}
//client端都一样，没必要重复写，写好服务器端即可