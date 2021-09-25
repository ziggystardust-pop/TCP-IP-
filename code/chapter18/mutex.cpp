#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<semaphore.h>
#define NUM_THREAD 100

long long sum = 0;
pthread_mutex_t mutex;

void* thread_inc(void* arg){
    pthread_mutex_lock(&mutex);
    for(int i = 0;i<50000000;i++){
        sum+=i;
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void* thread_des(void* arg){
    pthread_mutex_lock(&mutex);
    for(int i = 0;i<50000000;i++){
        sum-=i;
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main()
{
    pthread_t thread_id[NUM_THREAD];
    printf("sizeof long long:%d\n",sizeof(long long));
    pthread_mutex_init(&mutex,NULL);

    for(int i = 0;i<NUM_THREAD;i++){
        if(i%2){
            pthread_create(&(thread_id[i]),NULL,thread_inc,NULL);

        }
        else{
            pthread_create(&(thread_id[i]),NULL,thread_des,NULL);
        }
    }
    for(int i = 0;i<NUM_THREAD;i++){
        pthread_join(thread_id[i],NULL);
    }

    printf("result:%lld\n",sum);

    //创建一百个线程，一半执行函数1，一半执行函数2
    // 最后结果正确应为0
    pthread_mutex_destroy(&mutex);

    return 0;

}