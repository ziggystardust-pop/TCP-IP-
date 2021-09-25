#include<stdio.h>
#include<unistd.h>


int main(){
    //复制自动打开的标准输出文件描述符1，使用复制的文件描述符输出
    // 自动打开的0，1，2描述符与套接字文件描述符并无区别
    int cfd1,cfd2;
    char str1[] = "hi\n";
    char str2[] = "hello";
    cfd1 = dup(1);
    cfd2 = dup2(cfd1,7);
    printf("fd1 = %d , fd2 = %d\n",cfd1,cfd2);
    write(cfd1,str1,sizeof(str1));
    write(cfd2,str2,sizeof(str2));
    close(cfd1);
    close(cfd2);//终止复制的文件描述符但是还有原本的描述符，所以仍然可以输出
    write(1,str1,sizeof(str1));
    close(1);
    write(1,str2,sizeof(str2));//无法输出
    return 0;
}