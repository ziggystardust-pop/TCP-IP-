#include<stdio.h>
#include<fcntl.h>


int main()
{
    FILE *fp;
    int fd = open("data.dat",O_WRONLY|O_CREAT|O_TRUNC);
    if(fd==-1){
        fputs("file open error",stdout);
        return -1;
    }
    printf("first file descriptor:%d\n",fd);

    fp = fdopen(fd,"w");//返回写模式的FILE指针
    fputs("tcp socket program",fp);//标准输出函数
    printf("second file descriptor:%d\n",fileno(fp));
    
    fclose(fp);//利用FILE指针关闭文件，此时无需再通过文件描述符关闭
  //调用fclose后文件描述符变为毫无意义的整数
  
    return 0;
}