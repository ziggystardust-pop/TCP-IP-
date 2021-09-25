#include<stdio.h>
#include<unistd.h>

int gval = 10;

int main()
{
    pid_t pid;
    int val = 20;
    gval++; val++;
    pid = fork();
    if(pid==0){
        gval+=2;
        val+=2;
    }
    else{
        gval-=2;
        val-=2;
    }
    if(pid==0){
        printf("child [%d,%d]\n",gval,val);
    }
    else{
        printf("parent [%d,%d]\n",gval,val);
    }
    return 0;
}