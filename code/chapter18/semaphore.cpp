#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<semaphore.h>

static int num;

pthread_mutex_t mutex;
static sem_t sem_one,sem_two;
void* thread_inc(void* arg){

    for(int i = 0;i<5;i++){
        fputs("input: ",stdout);
        sem_wait(&sem_two);
        scanf("%d",&num);
        sem_post(&sem_one);
    }

    return NULL;
}

void* thread_des(void* arg){
    int sum = 0;
    for(int i = 0;i<5;i++){
            sem_wait(&sem_one);

        sum+=num;
            sem_post(&sem_two);

    }
        printf("result:%d\n",sum);

    return NULL;
}

int main()
{

    pthread_t id1,id2;
    sem_init(&sem_one,0,0);
    
    sem_init(&sem_two,0,1);
    pthread_create(&id1,NULL,thread_inc,NULL);
    pthread_create(&id2,NULL,thread_des,NULL);
    pthread_join(id1,NULL);
    pthread_join(id2,NULL);



    sem_destroy(&sem_one);
    sem_destroy(&sem_two);
    return 0;

}