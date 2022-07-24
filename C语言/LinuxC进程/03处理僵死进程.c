#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
/* 僵尸进程的概念：

若子进程死了，父进程还活着，但是父进程没有调用wait 或者 waitpid函数完成对子进程的回收时（或者说父进程调用waitpid函数对其子进程进行回收时，子进程还活着，且waitpid函数的options==WNOHANG非阻塞的），此时的子进程就变成僵尸进程。

当子进程先退出，而父进程没有完成对子进程资源的回收，此时的子进程就会变成僵尸进程！）*/
//waitpid函数测试代码,测试让父进程调用waitpid函数回收子进程资源！
int main()
{
	printf("before fork: pid==[%d]\n",getpid());
	int i = 0;
	for(;i<3;++i){
		//循环创建3个子进程
		pid_t pid = fork();
		if(pid < 0){
			perror("fork error!");
			return -1;
		}
		else if(pid==0){//当前进程为 子进程
			printf("child process: pid==[%d],fpid==[%d]\n",getpid(),getppid());
			sleep(2);
			break;//这个break语句会保证所创建的子进程都为兄弟子进程
		}
		else{//pid > 0 当前进程为 父进程
			printf("father process: pid==[%d],fpid==[%d]\n",getpid(),getppid());
			//在父进程中调用waitpid函数!
			pid_t inputPid = -1;//inputPid==-1表示我要回收当前所有的子进程
            //即等待着任一子进程do回收的意思
			int* wstatus = NULL;//status == NULL表示我不关心子进程的退出状态
			int options = 0;//options==0表示该函数是阻塞的
			pid_t exit_waitpid_pid = waitpid(inputPid,wstatus,options);
			if(exit_waitpid_pid > 0){//表示成功回收掉子进程了!
				printf("成功回收掉子进程了,此时所回收掉的子进程id==[%d]\n",exit_waitpid_pid);
			}
			else if(exit_waitpid_pid == -1){
				printf("当前没有需要回收掉的子进程了!\n");
			}
			else if(exit_waitpid_pid == 0 && options == WNOHANG){
				printf("当前需要回收的子进程还在运行中,尚未退出!\n");
			}
		}
		printf("\n");
	}
	return 0;
}
//只有父进程才能回收子进程，不能自己回收自己