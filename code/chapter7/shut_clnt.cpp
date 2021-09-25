
/*
//用于半关闭的函数：
int shutdown(int sock,int howto);
// sock:需要断开的socket文件描述符
// howto：传递断开方式
第二个参数：
SHUT_RD ： 断开输入流（无法接收数据，无法调用输入相关函数，输入缓冲中收到的数据也会删去）
SHUT_WR ： 断开输出流 （无法传输数据，但是输出缓冲中未传输完毕的数据，仍将传递至目标主机）
SHUT_RDWR ： 同时断开I/O流
*/

#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define BUF_SIZE 30

void error_handling(char *message);

// connect()请求连接函数


int main(int argc,char* argv[]){
    int sock;
    sockaddr_in serv_addr;
    char buf[BUF_SIZE];
    int str_len;
    int read_cnt;
    FILE* fp;
    fp = fopen("receive.dat","wb");

    if(argc!=3){
        printf("Usage:%s<ip> <port>\n",argv[0]);
        exit(1);
    }

    sock = socket(PF_INET,SOCK_STREAM,0);
    if(sock==-1){
        error_handling("socket() error");
    }

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1){
        error_handling("connect() error");
    }

    while((read_cnt = read(sock,buf,BUF_SIZE))!=0){
        fwrite((void*)buf,1,read_cnt,fp);
    }
    puts("received file data");

    write(sock,"thank you",10);
    fclose(fp);
    close(sock);
    return 0;
}
void error_handling(char *message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}