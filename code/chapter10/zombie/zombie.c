#include<stdio.h>
#include<unistd.h>

int main()
{
    pid_t pid = fork();
    if(pid==0){
        puts("i am a child process");
    }
    else{
        printf("child process id:%d\n",pid);
        sleep(30);//让父进程暂停30秒，防止父进程终止时将僵尸进程同时销毁

    }

    if(pid == 0){
        puts("end child process");
    }
    else{
        puts("end parent process");
    }

    return 0;
}