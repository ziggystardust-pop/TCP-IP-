#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

void * thread_main(void* arg){
    int cnt = *((int*)arg);
    for(int i = 0;i<cnt;i++){
        sleep(1);
        puts("running thread\n");
    }
    return NULL;
}

int main()
{
    pthread_t id;
    int thread_param = 5;
    pthread_create(&id,NULL,thread_main,(void*)&thread_param);//请求创建一个线程，并从传入的函数调用开始，在单独的执行流中运行
    sleep(10);
    puts("end of main");

    return 0;
}