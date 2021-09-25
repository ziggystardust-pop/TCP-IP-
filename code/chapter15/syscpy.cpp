#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>

#define BUF_SIZE 3

int main()
{
    FILE* fd1,*fd2;
    char buf[BUF_SIZE];
    //基于缓冲的复制，使用标准I/O函数
    fd1 = fopen("news.txt","r");
    fd2 = fopen("cpy.txt","w");

    while(fgets(buf,BUF_SIZE,fd1)!=NULL){
        fputs(buf,fd2);

    }
    fclose(fd1);
    fclose(fd2);
    return 0;
}