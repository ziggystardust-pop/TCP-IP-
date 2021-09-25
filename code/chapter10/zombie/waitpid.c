#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/wait.h>
int main()
{
    int status;
    pid_t pid = fork();
    if(pid==0){
        sleep(15);
        return 24;
    }
    else{
        while(!waitpid(-1,&status,WNOHANG)){
            sleep(3);
            puts("sleep  3sec");//验证不会阻塞
        }

    }
    if(WIFEXITED(status)){
        printf("child send %d\n",WEXITSTATUS(status));
    }
    return 0;
}