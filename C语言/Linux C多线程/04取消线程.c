#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
void *Test(void*arg){
    printf("子线程: %ld \n",pthread_self());
    return NULL;
}

int main(){
    pthread_t tid;
    printf("主线程: %ld \n",pthread_self());
    pthread_create(&tid,NULL,Test,NULL);
    if(pthread_cancel(tid))//杀死子线程
    {
        printf("终止线程失败");
    }
    pthread_exit(NULL);//子线程自己结束
}
//杀死子线程必须是子线程调用了系统函数，printf就是包装了系统函数，间接调用，一样的，所以在打印了第一个后就打印不出来了。