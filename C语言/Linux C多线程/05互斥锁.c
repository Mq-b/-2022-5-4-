#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define MAX 50
int number;//全局变量，共享资源
pthread_mutex_t mutex;//创建互斥锁

void* funcA_num(void*arg){
    for(int i=0;i<MAX;i++){
        pthread_mutex_lock(&mutex);//上锁
        int cur=number;
        cur++;
        number=cur;
        pthread_mutex_unlock(&mutex);//解锁
        printf("Thread A,id = %lu, number = %d\n",pthread_self(),number);
        usleep(2);
    }
    return NULL;
}
void* funcB_num(void*arg){
    for(int i=0;i<MAX;i++){
        pthread_mutex_lock(&mutex);//上锁
        int cur=number;
        cur++;
        number=cur;
        pthread_mutex_unlock(&mutex);//解锁
        printf("Thread B,id = %lu, number = %d\n",pthread_self(),number);
        usleep(2);
    }
    return NULL;
}

int main(){
    pthread_t p1 ,p2;
    pthread_mutex_init(&mutex,NULL);//初始化互斥锁
    //创建两个子线程
    pthread_create(&p1,NULL,funcA_num,NULL);
    pthread_create(&p2,NULL,funcB_num,NULL);
    //合并子线程回收资源
    pthread_detach(p1);
    pthread_detach(p2);
    pthread_exit(NULL);
    pthread_mutex_destroy(&mutex);//回收互斥锁资源
}