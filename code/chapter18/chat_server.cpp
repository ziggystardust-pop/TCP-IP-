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


int main()
{
    int serv_sock,clnt_sock;
    struct sockaddr_in serv_adr,clnt_adr;
    int clnt_adr_sz;
    pthread_t t_id;
    
}