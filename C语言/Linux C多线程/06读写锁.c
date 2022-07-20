#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define MAX 50
int number;//全局变量，共享资源
pthread_rwlock_t rwlock;//创建读写锁

void* read_num(void*arg){//读函数
    for(int i=0;i<MAX;i++){
        pthread_rwlock_wrlock(&rwlock);//上锁
        pthread_rwlock_unlock(&rwlock);//解锁
        printf("Read ,id = %lu, number = %d\n",pthread_self(),number);
        usleep(rand()%5);//让线程堵塞休眠
    }
    return NULL;
}
void* write_num(void*arg){//写函数
    for(int i=0;i<MAX;i++){
        pthread_rwlock_wrlock(&rwlock);//上锁
        int cur=number;
        cur++;
        number=cur;
        pthread_rwlock_unlock(&rwlock);//解锁
        printf("Write ,id = %lu, number = %d\n",pthread_self(),number);
        usleep(2);
    }
    return NULL;
}

int main(){
    pthread_t p1[5] ,p2[3];//读五个 写三个
    pthread_rwlock_init(&rwlock,NULL);//初始化读写锁
    
    for(int i=0;i<5;i++){
        pthread_create(&p1[i],NULL,read_num,NULL);
    }
    for(int i=0;i<3;i++){
        pthread_create(&p2[i],NULL,write_num,NULL);
    }

    //合并子线程回收资源
    for(int i=0;i<3;i++){//回收写子线程
        pthread_join(p2[i],NULL);
    }
    for(int i=0;i<5;i++){//回收读子线程
        pthread_join(p1[i],NULL);
    }

    pthread_rwlock_destroy(&rwlock);//回收读写锁资源
}
/*1.读写锁机制：

    写者：写者使用写锁，如果当前没有读者，也没有其他写者，写者立即获得写锁；否则写者将等待，直到没有读者和写者。
    读者：读者使用读锁，如果当前没有写者，读者立即获得读锁；否则读者等待，直到没有写者。 

2.读写锁特性：

    同一时刻只有一个线程可以获得写锁，同一时刻可以有多个线程获得读锁。
    读写锁出于写锁状态时，所有试图对读写锁加锁的线程，不管是读者试图加读锁，还是写者试图加写锁，都会被阻塞。
    读写锁处于读锁状态时，有写者试图加写锁时，之后的其他线程的读锁请求会被阻塞，以避免写者长时间的不写锁。*/