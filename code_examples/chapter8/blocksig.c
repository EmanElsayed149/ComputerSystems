#include "csapp.h"

void sigint_handler(int sig)
{
    return;   /*change default to return instead of terminate */
}

void snooze(int secs)
{
    int rs = sleep(secs);
    printf("slept for %d of %d secs\n",secs-rs,secs);
    return;
}

int main(int argc , char **argv)
{
    sigset_t mask,prev_mask;
    if(argc != 2) //number of commandlines
    {
        fprintf(stderr,"usage:  %s <secs>\n",argv[0]);
        exit(0);
    }
    if((signal(SIGINT,sigint_handler))==SIG_ERR)
    {
        perror("signal error\n");
    }
    sigemptyset(&mask);
    sigaddset(&mask,SIGINT);
    /*block SIGINT and save pervoius blocked set */
    sigprocmask(SIG_BLOCK,&mask,&prev_mask);
    //code region that will not be interrupted by SIGINT
    snooze(atoi(argv[1]));
    /*restore previous blockde set , unblocking SIGINT*/
    sigprocmask(SIG_SETMASK,&prev_mask,NULL);
    snooze(atoi(argv[1]));
    exit(0);
}