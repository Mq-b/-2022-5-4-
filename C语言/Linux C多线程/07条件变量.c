#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

pthread_cond_t cond;
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
        pthread_mutex_lock(&mutex);
        //创建新节点
        struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
        //init node
        newNode->number=rand()%1000;
        newNode->next=head;
        head=newNode;
        printf("生产者, ID: %ld , number: %d\n",pthread_self(),newNode->number);
        pthread_mutex_unlock(&mutex);
        pthread_cond_broadcast(&cond);//唤醒所有阻塞的消费者线程 自动把互斥量锁上
        sleep(1);
    }
    return NULL;
}

//消费者
void*consumer(void*arg){
    while(1){
        pthread_mutex_lock(&mutex);
        while(head==NULL){//节点为空的情况
            //阻塞当前线程 等待生产者线程唤醒 同时解锁互斥量 也就不会导致死锁了，生产者和消费者共同的一个互斥量(锁)。
            pthread_cond_wait(&cond,&mutex);
        }
        struct Node*node=head;
        printf("消费者, ID: %ld , number: %d\n",pthread_self(),node->number);
        head=head->next;
        free(node);//释放节点内存
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

int main(){
    pthread_mutex_init(&mutex,NULL);//初始化互斥量
    pthread_cond_init(&cond,NULL);//初始化条件变量

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
    pthread_mutex_destroy(&mutex);//释放互斥量
    pthread_cond_destroy(&cond);//释放条件变量
}
/*线程阻塞函数, 哪个线程调用这个函数, 哪个线程就会被阻塞
int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex);

通过函数原型可以看出，该函数在阻塞线程的时候，需要一个互斥锁参数，这个互斥锁主要功能是进行线程同步，让线程顺序进入临界区，避免出现数共享资源的数据混乱。该函数会对这个互斥锁做以下几件事情：

在阻塞线程时候，如果线程已经对互斥锁 mutex 上锁，那么会将这把锁打开，这样做是为了避免死锁
当线程解除阻塞的时候，函数内部会帮助这个线程再次将这个 mutex 互斥锁锁上，继续向下访问临界区*/

//pthread_cond_signal 是唤醒至少一个被阻塞的线程（总个数不定），pthread_cond_broadcast 是唤醒所有被阻塞的线程