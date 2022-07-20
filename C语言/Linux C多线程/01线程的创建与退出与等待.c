#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

struct Test{
    int num;
    int age;
};

struct Test t;

void* callback(void*arg){
    for(int i=0;i<5;i++){
        printf("子线程:i= %d\n",i);
    }
    printf("子线程: %ld\n",pthread_self());
    t.num=100;
    t.age=6;
    pthread_exit(&t);//返回数据同时退出线程

    return NULL;
}

int main(){
    //每一个线程都有一个ID，c使用pthread_t pthread_self(void);得到线程ID
    //void pthread_exit(void*retval);退出线程函数
    pthread_t tid;
    pthread_create(&tid,NULL,callback,NULL);
    //usleep(1);//延迟挂起线程
    printf("主线程: %ld",pthread_self());
    void*ptr;
    pthread_join(tid,&ptr);//第二个参数是一个void**指针,这个函数的作用就是等待子线程结束，堵塞再这里，和c++的join差不多，如果子线程传递了数据，那么就会让第二个参数接收
    struct Test*pt=(struct Test*)ptr;
    printf("num: %d ,age: %d \n",pt->num,pt->age);
    //pthread_exit(NULL);//主线程退出
    //主线程提前退出，不会影响子线程，子线程依旧会自己执行
}

//进程会等待所有线程执行完毕再结束，回收资源。主线程停止，进程没停止，所以子线程依旧会运行完毕。但是如果没有使用pthread_exit(NULL);
//而是主线程main正常执行完，而子线程还没结束，那就会回收子线程的地址空间和资源。
//结构体创建在全局是因为如果在子线程创建，那么子线程结束后，栈空间就被回收了，所以要写在全局区。
