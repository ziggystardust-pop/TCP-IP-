#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include<netinet/in.h>
#include<fcntl.h>
#include<signal.h>

// socket函数创建socket

// bind函数为socket分配ip地址和端口号

// listen函数将socket转换为可接收链接的状态

int acpt_sock,recv_sock;
// accept函数用于接收对方的连接请求

//服务端同一时刻只与一个客户端相连
// 依次与五个客户端通信
#define BUFSIZE 30

void error_handling(char *message);
void urg_handler(int signo);
int main(int argc,char *argv[]){

    struct sockaddr_in recv_adr,serv_adr;
    socklen_t serv_adr_sz;
    struct sigaction act;
    char buf[BUFSIZE];
    int str_len,state;
    sockaddr_in serv_addr;
    if(argc!=2){
        printf("Usage:%s <port>",argv[0]);//打印使用方法
        exit(1);
    }
    act.sa_handler = urg_handler;
    sigemptyset(&act.sa_mask);
    acpt_sock = socket(PF_INET,SOCK_STREAM,0);
    act.sa_flags = 0;


// 指定ip地址和端口号和ip协议族
    memset(&serv_addr,0,sizeof(serv_addr));
    recv_adr.sin_family = AF_INET;
    recv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    recv_adr.sin_port = htons(atoi(argv[1]));
    if(bind(acpt_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1){
        error_handling("bind() error");
    }
    if(listen(acpt_sock,5)==-1){
        error_handling("listen() error");
    }



        serv_adr_sz = sizeof(serv_adr);
        recv_sock=accept(acpt_sock,(struct sockaddr*)&serv_adr,&serv_adr_sz);
        fcntl(recv_sock,F_SETOWN,getpid());
        //收到紧急消息时，操作系统产生SIGURG信号，调用信号处理函数
        state = sigaction(SIGURG,&act,0);

        while((str_len=recv(recv_sock,buf,sizeof(buf),0))!=0){
            if(str_len==-1){
                continue;
            }
            buf[str_len] = 0;
            puts(buf);;

        }
        close(recv_sock);
        close(acpt_sock);

    return 0;
}
void error_handling(char *message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}
void urg_handler(int signo){
    int str_len;
    char buf[BUFSIZE];
    str_len = recv(recv_sock,buf,sizeof(buf)-1,MSG_OOB);
    buf[str_len] = 0;
    printf("Urgent message : %s\n",buf);

}