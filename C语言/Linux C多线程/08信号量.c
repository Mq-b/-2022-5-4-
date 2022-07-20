#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>//提供信号量

//生产者的信号量
sem_t semp;
//消费者的信号量
sem_t semc;

pthread_mutex_t mutex;

//链表的节点类型
struct Node{
    int number;
    struct Node*next;
};

//链表头节点
struct Node*head=NULL;

//生产者
void*producer(void*arg){
    while(1){
        sem_wait(&semp);//先判断如果为0就阻塞 生产者资源-1
        pthread_mutex_lock(&mutex);//上锁
        //创建新节点
        struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
        //init node
        newNode->number=rand()%1000;
        newNode->next=head;
        head=newNode;
        printf("生产者, ID: %ld , number: %d\n",pthread_self(),newNode->number);
        pthread_mutex_unlock(&mutex);//解锁
        sem_post(&semc);//消费者资源+1
        sleep(1);
    }
    return NULL;
}
//消费者
void*consumer(void*arg){
    while(1){
        sem_wait(&semc);//先判断如果为0就阻塞 消费者资源-1
        pthread_mutex_lock(&mutex);//上锁
        struct Node*node=head;
        printf("消费者, ID: %ld , number: %d\n",pthread_self(),node->number);
        head=head->next;
        free(node);//释放节点内存
        pthread_mutex_unlock(&mutex);//解锁
        sem_post(&semp);//生产者资源+1
        sleep(1);
    }
    return NULL;
}

int main(){
    //生产者 初始化资源为5 有五个线程进行生产
    sem_init(&semp,0,5);
    //消费者 资源数量初始化为0，消费者线程启动就阻塞了
    sem_init(&semc,0,0);
    pthread_mutex_init(&mutex,NULL);
    pthread_t t1[5],t2[5];
    for(int i=0;i<5;i++){//创建生产者线程
        pthread_create(&t1[i],NULL,producer,NULL);
    }
    for(int i=0;i<5;i++){//创建消费者线程
        pthread_create(&t2[i],NULL,consumer,NULL);
    }

    for(int i=0;i<5;i++){//等待合并生产者线程回收资源
        pthread_join(t1[i],NULL);
    }
    for(int i=0;i<5;i++){//等待合并消费者线程回收资源
        pthread_join(t2[i],NULL);
    }

    sem_destroy(&semp);//删除信号量
    sem_destroy(&semc);
}
//共享资源唯一的时候可以不加锁

//与条件变量不同 信号量堵塞不会解锁互斥量。我们的例子是，生产者生产一个，消费者的资源+1，消费者就可以运行，反之亦然。
