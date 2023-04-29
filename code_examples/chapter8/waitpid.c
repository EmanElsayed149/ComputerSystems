#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>     
#include <sys/wait.h>     //for waitpid fun
#include <unistd.h>
#include <errno.h>        // for perror and errno 
#define N 2
int main()
{
    int status,i;
    pid_t pid;
    /*parent creates N children*/
    for(i=0;i<N;i++)
    {
        if((pid=fork())==0)
           exit(100+i);      /*child status*/
    }

    /*parent reaps N children in no particular order*/
    while((pid = waitpid(-1,&status,0))>0)
    {
        if(WIFEXITED(status))
        {
            printf("child %d terminated normally with exit status %d\n",pid,WEXITSTATUS(status));
        }
        else
        {
            printf("child %d terminated abnormally\n",pid);
        }
    }

    /*the only normal termination for waitpid is if there are no mare children*/
    if(errno != ECHILD)
    {
        perror("eaitpid error");
    }
    exit(0);
    
}