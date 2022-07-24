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

int main(void){
    pid_t pid;
    if((pid=fork())<0){
        sys_err("fork");
    }else if(pid==0){
        printf("child process PID is %d\n",getpid());//当前进程ID
        printf("Group ID of child is %d\n",getpgid(0));//获取进程组ID
        printf("Session ID of child is %d\n",getsid(0));//获取当前子进程的会话id
        sleep(1);
        setsid();//创建一个会话，并以自己的ID设置进程组ID，同时也是新会话的ID成功返回调用进程的会话ID，失败返回-1


        printf("Changed:\n");

        printf("child process PID is %d\n",getpid());//当前进程ID
        printf("Group ID of child is %d\n",getpgid(0));//获取进程组ID
        printf("Session ID of child is %d\n",getsid(0));//获取当前子进程的会话id
    }
    return 0;
}
/*创建会话的6点注意事项：
1.	调用进程不能是进程组组长，该进程变成新会话首进程
2.	该进程成为一个新进程组的组长进程
3.	需要root权限（ubuntu不需要）
4.	新会话丢弃原有的控制终端，该会话没有控制终端
5.	该调用进程是组长进程，则出错返回
6.	建立新会话时，先调用fork，父进程终止，子进程调用setsid
*/