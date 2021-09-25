#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>


int main(){

    int status;
    pid_t pid = fork();
    if(pid==0){
        //子进程
        return 3;
    }
    else{
        printf("child pid : %d\n",pid);//在父进程打印对应打印子进程的id
        pid = fork();
        if(pid==0){
            exit(7);

        }
        else{//此前创建了两个子进程
            printf("child pid : %d\n",pid);
            wait(&status);
            //向wait函数传递status地址后应写出：
            if(WIFEXITED(status)){              
                printf("child one send:%d",WEXITSTATUS(status));
            }
            wait(&status);//因为创建了两个进程所以要调用两次
            if(WIFEXITED(status)){              
                printf("child two send:%d",WEXITSTATUS(status));
            }
            sleep(30);

        }

    }
    
    return 0;
}