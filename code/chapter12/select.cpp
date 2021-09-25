#include<unistd.h>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/time.h>


#define BUF_SIZE 30
int main()
{
    fd_set reads,temps;
    int result,str_len;
    char buf[BUF_SIZE];
    struct timeval timeout;
    FD_ZERO(&reads);
    //监视标准输入的变化
    // 使用fd_set数组，如果所在位的值为1则代表此下标对应的文件描述符是监视对象


    FD_SET(0,&reads);

    // timeout.tv_sec = 5;
    // timeout.tv_usec = 5000;

    while(1){
        temps = reads;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        result = select(1,&temps,0,0,&timeout);
        if(result==-1){
            puts("select error!");
            break;
        }
        else if(result==0){
            puts("timeout!");
        }
        else{
            if(FD_ISSET(0,&temps)){
                str_len = read(0,buf,BUF_SIZE);
                buf[str_len] = 0;
                printf("message from console:%s",buf);

            }
        }
    }

    //调用selet后，出了发生变化的文件描述符的对应位外，都将变为0
    // 为了记住初始值，必须进行reads到temps的复制过程
    // 调用select函数后，每次超时时间的值都会被替换为超时前的剩余时间，所以要在循环中定义超时时间

    return 0;
}