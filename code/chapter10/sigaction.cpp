#include<iostream>
#include<unistd.h>
#include<signal.h>
#include<stdio.h>

using namespace std;

void timeout(int sig){
    if(sig==SIGALRM){
        puts("time out!");
    }
    alarm(2);

}

int main()
{
    int i;
    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = timeout;
    sigemptyset(&act.sa_mask);
    sigaction(SIGALRM,&act,0);
    alarm(2);
    for(int i = 0;i<3;i++){
        puts("wait");
        sleep(100);
    }
    return 0;
}