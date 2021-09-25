#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>

#define BUF_SIZE 30


void error_handling(char *message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

void read_childproc(int sig){
    int status;
    pid_t id = waitpid(-1,&status,WNOHANG);
    if(WIFEXITED(status)){
        printf("removed proc id : %d\n",id);
        printf("child send : %d\n",WEXITSTATUS(status));
    }
}


int main(int argc,char *argv[]){

    int serv_sock,clnt_sock;

    sockaddr_in serv_adr,clnt_adr;
    pid_t pid;
    struct sigaction act;
    socklen_t adr_sz;
    int str_len,state;
    char buf[BUF_SIZE];
    int fds[2];
    if(argc!=2){
        printf("Usage:%s <port>",argv[0]);//打印使用方法
        exit(1);
    }
    act.sa_handler = read_childproc;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGCHLD,&act,0);
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
    pipe(fds);
    pid = fork();
    if(pid==0){
        FILE * fp = fopen("echomsg.txt","wt");
        char msgbuf[BUF_SIZE];
        int i,len;
        for(int i = 0;i<10;i++){
            len = read(fds[0],msgbuf,BUF_SIZE);
            fwrite((void*)msgbuf,1,len,fp);

        }
        fclose(fp);
        return 0;
    }
    //五个客户端则要生成五个用于I/O的socket
    //使用循环
    // 要实现echo则在每次循环中使用while，一直接收和发送信息，直到用户输入q（quit）
    while(1){
        adr_sz = sizeof(clnt_adr);
        clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_adr,&adr_sz);
        if(clnt_sock==-1){
            continue;
        }
        else{
            puts("new client connected");
        }
        pid = fork();
  
        if(pid==0){
            close(serv_sock);
            while((str_len=read(clnt_sock,buf,BUF_SIZE))!=0)
            {
                write(clnt_sock,buf,str_len);
                write(fds[1],buf,str_len);
            }   
            close(clnt_sock);
            puts("client discon");
            return 0;    
        }
        else{
            close(clnt_sock);
        }
    }
    close(serv_sock);
    return 0;
}