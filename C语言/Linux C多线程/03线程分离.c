#include<pthread.h>
#include<stdio.h>

struct Test{
    int num;
    int age;
};

void* callback(void*arg){
    for(int i=0;i<5;i++){
        printf("子线程:i= %d\n",i);
    }
    printf("子线程: %ld\n",pthread_self());
    struct Test* t=(struct Test*)arg;
    t->num=100;
    t->age=6;
    return NULL;
}

int main(){
    pthread_t tid;
    struct Test t;
    printf("主线程: %ld",pthread_self());
    pthread_create(&tid,NULL,callback,&t);//传入结构体

    pthread_detach(tid);//线程分离,当子线程退出的时候，其占用的内核资源被系统的其他进程接管并回收。而不用像join一样主线程必须等待子线程执行完毕，且承担回收资源的工作。
    
    pthread_exit(NULL);
}