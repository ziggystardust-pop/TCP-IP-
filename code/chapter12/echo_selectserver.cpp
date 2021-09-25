#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/select.h>

#define BUF_SIZE 100
void error_handling(char *buf);

int main(int argc,char *argv[])
{
    int serv_sock,clnt_sock;
    struct sockaddr_in serv_adr,clnt_adr;
    struct timeval timeout;
    fd_set reads,cpy_reads;

    socklen_t adr_sz;
    int fd_max,str_len,fd_num,i;

    char buf[BUF_SIZE];
    if(argc!=2){
        printf("Usage:%s <port>",argv[0]);//打印使用方法
        exit(1);
    }
    serv_sock = socket(PF_INET,SOCK_STREAM,0);

// 指定ip地址和端口号和ip协议族
    memset(&serv_adr,0,sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));
    if(bind(serv_sock,(struct sockaddr*)&serv_adr,sizeof(serv_adr))==-1){
        error_handling("bind() error");
    }
    if(listen(serv_sock,5)==-1){
        error_handling("listen() error");
    }

    // 初始化reads数组为全0
    FD_ZERO(&reads);
    //向reads（select的第二个参数）注册服务器端套接字，
    // 如此接收数据的监视对象就包含了服务器端套接字
    // 客户端的连接请求同样通过传输数据完成，这样如果服务器端套接字中有接收的数据
    // 则代表有新的连接请求
    FD_SET(serv_sock,&reads);
    fd_max = serv_sock;

    while(1){
        cpy_reads = reads;//使用select的必备流程
        timeout.tv_sec = 5;
        timeout.tv_usec = 5000;
        //调用select函数，传入监视对象的最大数（范围），和cpy_reads(根据监视的目的传递参数)
        if((fd_num=select(fd_max+1,&cpy_reads,0,0,&timeout))==-1){
            break;
        }
        if(fd_num==0){
            continue;
        }
        //查找有变化的套接字文件描述符（有接收数据的套接字）
        for(int i = 0;i<fd_max+1;i++){
            if(FD_ISSET(i,&cpy_reads)){
                //如果有变化
                // 验证是否时服务器端套接字发生变化
                if(i==serv_sock){
                    //受理连接请求
                    adr_sz = sizeof(clnt_adr);
                    clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_sock,&adr_sz);
                    FD_SET(clnt_sock,&reads);//????????????????????
                    if(fd_max<clnt_sock){
                        fd_max = clnt_sock;
                    }    
                    printf("connected client:%d\n",clnt_sock);

                }
                else{
                    //发生变化的并非服务器端套接字，而是有要接受的数据时
                    // 先确认是要接受的数据还是代表断开连接的EOF
                    str_len = read(i,buf,BUF_SIZE);
                    if(str_len==0){
                        FD_CLR(i,&reads);//关闭连接
                        close(i);
                        printf("close client :%d\n",i);

                    }
                    else{
                        write(i,buf,str_len);//回声，此时传来的不是EOF

                    }
                }
            }
        }
    }
    close(serv_sock);
    return 0;
}

void error_handling(char *buf){
    fputs(buf,stderr);
    fputc('\n',stderr);
    exit(1);
}