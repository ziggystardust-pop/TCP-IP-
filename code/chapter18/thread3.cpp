#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int sum = 0;

void * thread_sum(void* arg){
    int s = ((int*)arg)[0];
    int e = ((int*)arg)[1];
    while(s<=e){
        sum+=s;
        s++;
    }
    return NULL;

}

int main()
{
    pthread_t id_t1,id_t2;
    int range1[] = {1,5};
    int range2[] = {6,10};
    pthread_create(&id_t1,NULL,thread_sum,(void*)range1);
    
    pthread_create(&id_t2,NULL,thread_sum,(void*)range2);

    pthread_join(id_t1,NULL);
    
    pthread_join(id_t2,NULL);
    printf("result:%d\n",sum);

    return 0;
//之所以可以算出正确结果完全是因为两个线程共享保存全局变量的数据区

}