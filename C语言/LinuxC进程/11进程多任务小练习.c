#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
    printf("主进程 ID= %d",getpid());
    int fd;
    fd=open("ps.txt",O_WRONLY|O_CREAT|O_TRUNC,0644);
    dup2(fd,STDOUT_FILENO);//重定向stdout，定向到fd，它储存了文件描述符,标注输出会输出到ps.out文件中
    printf("主进程 ID= %d",getpid());
    pid_t pid;
    for(int i=0;i<3;++i){
		//循环创建3个子进程
		pid = fork();
		if(pid < 0){
			perror("fork error!");
			return -1;
		}
		else if(pid==0){//当前进程为 子进程
            if(i==0){
            execl("./hello", "hello", NULL);
            }
            if(i==1){
            execlp("ps","ps","aux",NULL);
            }
            if(i==2){
            execlp("ls","-a","-l","-n","-i",NULL);
            }
		}
    }
    sleep(1);
    while(1){
        int options = WNOHANG;
		pid_t exit_waitpid_pid = waitpid(pid,NULL,options);
        if(exit_waitpid_pid==-1){
            printf("子进程全部退出完毕");
            break;
        }
    }
}