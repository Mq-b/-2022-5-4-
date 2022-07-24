/*waitpid函数:
pid_t waitpid(pid_t pid,int* status,int options);
    参数：
        pid:
            pid > 0:表示等待指定的子进程
            pid==-1:表示等待任一子进程
        status:
        同wait函数
        options:
            0:表示阻塞
            WNOHANG：表示不阻塞（不论有没有子进程退出，waitpid函数都会马上退出!不会阻塞在这儿！）
    返回值：
        > 0:是回收掉子进程的PID
        = 0:若options取值为WNOHANG,则表示子进程还活着
        -1:表示目前已经没有子进程了，此时那可以break掉循环回收子进程的while循环了！
 
    注意：调用一次waitpid/wait函数只能回收一个子进程而已！
 
灵魂拷问：为什么一定是由于父进程来调用wait/waitpid函数来对其子进程的资源进行回收呢？
答：因为子进程无法对自己的内核区PCB的资源进行回收！这个进程控制块的资源必须由其父进程去回收！
一旦子进程先于父进程先退出，则此时的子进程就会变成僵尸进程！那么就会浪费系统资源！*/
//waitpid函数测试代码,测试让父进程调用waitpid函数回收子进程资源！
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<stdlib.h>
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
			printf("\n");
			printf("第[%d]个子进程被父进程do循环回收工作:",i+1);
			printf("child process: pid==[%d],fpid==[%d]\n",getpid(),getppid());
			sleep(1);
			break;//这个break语句会保证所创建的子进程都为兄弟子进程
		}
		else{//pid > 0 当前进程为 父进程
			printf("father process: pid==[%d],fpid==[%d]\n",getpid(),getppid());
			//在父进程中调用waitpid函数!
			while(1){
				//这个while循环,就已经可以保证 父进程一定是晚于子进程退出的了！
				pid_t inputPid = -1;//inputPid==-1表示我要回收当前所有的子进程，如果是0那么表示本组进程
				int wstatus = -1;//&status != NULL表示我关心子进程的退出状态
									//后续需要结合wstatus的参数写代码了解子进程的退出状态
				int options = WNOHANG;//options==WNOHANG表示该函数是不阻塞的
				pid_t exit_waitpid_pid = waitpid(pid,&wstatus,options);
				if(exit_waitpid_pid > 0){//表示成功回收掉子进程了!
					printf("成功回收掉子进程了,此时所回收掉的子进程id==[%d]\n",exit_waitpid_pid);
					//成功回收掉子进程，才能够判断其退出状态！
					if(WIFEXITED(wstatus)){
						printf("子进程正常退出了!子进程的退出状态是：%d\n",WEXITSTATUS(wstatus));
					}else if(WIFSIGNALED(wstatus)){
						printf("子进程时由信号[%d]杀死的!\n",WTERMSIG(wstatus));
					}
				}
				else if(exit_waitpid_pid == 0 && options == WNOHANG){
					// printf("当前需要回收的子进程还在运行中,尚未退出!\n");
					//因为这句子进程尚在运行的话肯定是大量打印的！
                    //so这些测试代码可以在测试程序时使用，但是在实际项目中就注释掉了吧！
				}
				else if(exit_waitpid_pid == -1){
					printf("当前没有需要回收掉子进程了,即:活着的子进程都已经死掉了退出了!\n");
					printf("此时，没有需要回收掉子进程了,就直接break 退出循环,无需再do回收子进程资源的工作了!\n");
					break;//此时，没有需要回收掉子进程了，就直接break 退出循环，无需再do回收子进程资源的工作了！
				}
			}
		}
		printf("\n");
	}
	return 0;
}
//不管是wait还是waitpid，一次调用只能回收一个进程，要想多回收就得写while