// #include<unistd.h>
// #include<stdio.h>
// #include<stdlib.h>
// #include<netdb.h>
// #include<arpa/inet.h>
// #include<string.h>

// void error_handling(char *message){
//     fputs(message,stderr);
//     fputc('\n',stderr);
//     exit(1);
// }
// int main(int argc,char* argv[])
// {


//     //通过域名来获取IP地址
//     struct sockaddr_in addr;
    
//     struct hostent* host;
//     if(argc!=2){
//         printf("Usage:....\n");
//     }

//     memset(&addr,0,sizeof(addr));
//     addr.sin_addr.s_addr = inet_addr(argv[1]);

//     host = gethostbyaddr((char*)&addr.sin_addr,4,AF_INET);

//     //如果host为空
//     if(!host){
//         error_handling("gethost error");
//     }
//     printf("Official name:%s\n",host->h_name);

//     // 可能有多个域名，所以用循环
//     for(int i = 0;host->h_aliases[i];i++){
//         //当host->aliases[i]为空时跳出循环
//         printf("Aliases %d: %s\n",i+1,host->h_aliases[i]);
//     }
//     printf("Adress type:%s\n",(host->h_addrtype==AF_INET)?"AF_INET":"AF_INET6");
//     for(int i = 0;host->h_addr_list[i];i++){
//         //转换为in_addr结构体指针后再解引用
//         printf("IP addr %d %s\n",i+1,(inet_ntoa(*(struct in_addr*)host->h_addr_list[i])));
//     }
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int i;
    struct hostent *host;
    struct sockaddr_in addr;
    if (argc != 2)
    {
        printf("Usage : %s <IP>\n", argv[0]);
        exit(1);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    host = gethostbyaddr((char *)&addr.sin_addr, 4, AF_INET);
    if (!host)
        error_handling("gethost... error");

    printf("Official name: %s \n", host->h_name);
    for (i = 0; host->h_aliases[i]; i++)
        printf("Aliases %d:%s \n", i + 1, host->h_aliases[i]);
    printf("Address type: %s \n",
           (host->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6");

    for (i = 0; host->h_addr_list[i]; i++)
        printf("IP addr %d: %s \n", i + 1,
               inet_ntoa(*(struct in_addr *)host->h_addr_list[i]));

    return 0;
}
void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}