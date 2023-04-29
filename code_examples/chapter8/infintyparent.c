#include "csapp.h"
int main()
{
    pid_t pid;
    pid = fork();
    if(pid==0)  //child
    {
        printf("child pid %d",getpid());
        exit(0);
    }
    while(1);
}