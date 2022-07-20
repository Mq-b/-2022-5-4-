
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
    pthread_create(&tid,NULL,callback,&t);//传入结构体
    pthread_join(tid,NULL);//等待子线程运行完毕
    printf("num: %d ,age: %d \n",t.num,t.age);
}