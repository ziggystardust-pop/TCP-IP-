#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>


// socket函数创建socket

// bind函数为socket分配ip地址和端口号

// listen函数将socket转换为可接收链接的状态


// accept函数用于接收对方的连接请求

//服务端同一时刻只与一个客户端相连
// 依次与五个客户端通信
#define BUFSIZE 1024

void error_handling(char *message);

int main(int argc,char *argv[]){

    int serv_sock;
    sockaddr_in serv_addr;
    char message[] = "hello world!";
    if(argc!=2){
        printf("Usage:%s <port>",argv[0]);//打印使用方法
        exit(1);
    }
    serv_sock = socket(PF_INET,SOCK_STREAM,0);
    if(serv_sock==-1){
        error_handling("socket() error");
    }
    FILE* readfp;
    FILE* writefp;
// 指定ip地址和端口号和ip协议族
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1){
        error_handling("bind() error");
    }
    if(listen(serv_sock,5)==-1){
        error_handling("listen() error");
    }
    int str_len;
    int clnt_sock;
    sockaddr_in clnt_addr;
    socklen_t clint_addr_size;

    //五个客户端则要生成五个用于I/O的socket
    //使用循环
    // 要实现echo则在每次循环中使用while，一直接收和发送信息，直到用户输入q（quit）
    for(int i = 0;i<5;i++){

        clint_addr_size = sizeof(clnt_addr);
        clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&clint_addr_size);

        if(clnt_sock==-1){
            error_handling("accept() error");
        }
        else printf("Connected client %d\n",i+1);

        readfp = fdopen(clnt_sock,"r");
        writefp = fdopen(clnt_sock,"w");

        while (!feof(readfp))//注意加括号，防止优先级错误
        {
            fgets(message,BUFSIZE,readfp);
            fputs(message,writefp);
            fflush(writefp);//如果不调用此函数则无法保证立即将数据传输到客户端

        }
        fclose(readfp);
        fclose(writefp);        
    }
    close(serv_sock);
    return 0;
}
void error_handling(char *message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}