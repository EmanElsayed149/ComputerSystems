#include "csapp.h"

void sigint_handler(int sig)
{
    return;   /*change default to return instead of terminate */
}

void snooze(int secs)
{
    int rs = sleep(secs);
    printf("slept for %d of %d secs\n",secs-rs,secs);
    exit(0);
}

int main(int argc , char **argv)
{
    if(argc != 2) //number of commandlines
    {
        fprintf(stderr,"usage:  %s <secs>\n",argv[0]);
        exit(0);
    }
    if((signal(SIGINT,sigint_handler))==SIG_ERR)
    {
        perror("signal error\n");
    }
    snooze(atoi(argv[1]));
    exit(0);
}