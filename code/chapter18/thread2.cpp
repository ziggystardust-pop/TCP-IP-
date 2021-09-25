#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void * thread_main(void* arg){
    int cnt = *((int*)arg);
    for(int i = 0;i<cnt;i++){
        sleep(1);
        puts("running thread\n");
    }
    char*msg = (char*)malloc(sizeof(char)*50);
    strcpy(msg,"hello world\n");
    return (void*)msg;
}
int main()
{
    pthread_t id;
    int thread_param = 5;
    void* thr_ret;

    pthread_create(&id,NULL,thread_main,(void*)&thread_param);//请求创建一个线程，并从传入的函数调用开始，在单独的执行流中运行
    if(pthread_join(id,&thr_ret)!=0){
        //thr_ret中保存线程main函数的返回值，注意该返回值是函数内部动态分配的内存空间地址值
        puts("pthread_join() error");
        return -1;
    }
    printf("thread return message:%s\n",(char*)thr_ret);

    free(thr_ret);
    puts("end of main");

    return 0;
}