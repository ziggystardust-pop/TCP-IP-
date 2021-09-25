#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<semaphore.h>
#include<sys/epoll.h>

#define BUF_SIZE 100

#define EPOLL_SIZE 50    

int main(int argc,char* argv[])
{
    int serv_sock,clnt_sock;
    struct sockaddr_in serv_adr,clnt_adr;
    socklen_t adr_sz;
    int str_len;
    char buf[BUF_SIZE];
    if(argc!=2){
        printf("usage :%s <port>\n",argv[0]);
        exit(1);
    }
    serv_sock = socket(PF_INET,SOCK_STREAM,0);
    memset(&serv_adr,0,sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_port = htons(atoi(argv[1]));
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(serv_sock,(struct sockaddr*)&serv_adr,sizeof(serv_adr))==-1){
        printf("bind error\n");
    }

    struct epoll_event *ep_events;
    struct epoll_event event;
    int epfd,event_cnt;

    epfd = epoll_create(EPOLL_SIZE);
    event.events = EPOLLIN;
    // ep_events = malloc(sizeof(struct epoll_event)*EPOLL_SIZE);

    event.data.fd =serv_sock;
    epoll_ctl(epfd,EPOLL_CTL_ADD,serv_sock,&event);


}