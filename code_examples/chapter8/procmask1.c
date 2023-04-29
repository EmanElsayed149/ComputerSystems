/*warning : this code is buggy */
/* if kernal schedule to run child and signal of (termination parent) interrupted parent will delet child 
    before adding it in job list 
*/

#include "csapp.h"
void initjobs()
{

}
void addjob(int pid)
{

}
void deletejob(int pid)
{
    
}

void handler(int sig)
{
    int olderrno = errno;
    sigset_t mask_all, prev_all;
    pid_t pid;

    Sigfillset(&mask_all);
    while ((pid = waitpid(-1, NULL, 0)) > 0) { /* Reap a zombie child */
        Sigprocmask(SIG_BLOCK, &mask_all, &prev_all);
        deletejob(pid); /* Delete the child from the job list */
        Sigprocmask(SIG_SETMASK, &prev_all, NULL);
    }
    if (errno != ECHILD)
        Sio_error("waitpid error");
    errno = olderrno;

}

int main(int argc,char **argv)
{
    sigset_t mask_all,prev_all;
    int pid;
    Sigfillset(&mask_all);
    Signal(SIGCHLD,handler);
    initjobs();   /*initialize job list */

    while(1)
    {
        if((pid=fork())==0)
        {
            Execve("/bin/date", argv, NULL);
        }
        Sigprocmask(SIG_BLOCK,&mask_all,&prev_all);  /*block parent process*/
        addjob(pid);
        Sigprocmask(SIG_SETMASK,&prev_all,NULL);
    }
    exit(0);
}