#include<stdio.h>
#include<unistd.h>

#define BUF_SIZE 30
int main()
{
    int fds1[2];//用于存储用于I/O的文件描述符
    int fds2[2];    
    char str1[] = "Who are you?";
    char str2[] = "Thank you for your message";

    char buf[BUF_SIZE];
    pid_t pid;
    pipe(fds1);//创建管道，此时数组中有了描述符
    pipe(fds2);//创建管道，此时数组中有了描述符
    pid = fork();
    if(pid==0)
    {
        write(fds1[1],str1,sizeof(str1));//fds[1]为通过管道传输数据的文件描述符（管道入口）
        read(fds2[0],buf,BUF_SIZE);
        printf("child proc output:%s\n",buf);
    }
    else{
        read(fds1[0],buf,BUF_SIZE);
        printf("parent proc output:%s\n",buf);
        write(fds2[1],str2,sizeof(str2));
        sleep(3);
        //如果注释掉18行，则在第19行的代码将读出17行写入的数据，管道中就没有了数据
        // 父进程的第一个read将无限期的等待管道中被写入数据
    }
    return 0;
    
}