#include<stdio.h>
#include<unistd.h>

#define BUF_SIZE 30
int main()
{
    int fds[2];//用于存储用于I/O的文件描述符
    char str[] = "who are you?";
    char buf[BUF_SIZE];
    pid_t pid;
    pipe(fds);//创建管道，此时数组中有了描述符
    pid = fork();
    if(pid==0)
    {
        write(fds[1],str,sizeof(str));//fds[1]为通过管道传输数据的文件描述符（管道入口）
    }
    else{
        read(fds[0],buf,BUF_SIZE);
        puts(buf);
    }
    return 0;
    
}