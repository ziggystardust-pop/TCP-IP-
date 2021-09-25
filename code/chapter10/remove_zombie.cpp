//使信号处理技术消灭僵尸进程

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
#include<stdlib.h>

void read_childproc(int sig){
    int status;
    pid_t id = waitpid(-1,&status,WNOHANG);
    if(WIFEXITED(status)){
        printf("removed proc id : %d\n",id);
        printf("child send : %d\n",WEXITSTATUS(status));
    }
}

int main()
{
    pid_t pid;
    struct sigaction act;
    act.sa_handler = read_childproc;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGCHLD,&act,0);
    //第一个子进程
    pid = fork();
    //子进程：
    if(pid==0){
        puts("this is a child process");
        sleep(10);
        return 12;
    }
    else{//父进程执行区域
        printf("child process id:%d\n",pid);//打印第一个子进程的pid
        pid = fork();//创建第二个子进程
        if(pid==0){
            puts("this is second child process");
            sleep(10);
            exit(24);

        }
        else{
            printf("child process id:%d\n",pid);//打印第一个子进程的pid
            for(int i = 0;i<5;i++){
                puts("wait");
                sleep(5);
//为了等待SIGCHLD信号，使父进程共暂停5次，发生信号时，父进程会被唤醒，所以
// 实际暂停时间不到25秒
            }
        }
    }
    return 0;

}