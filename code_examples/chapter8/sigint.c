#include "csapp.h"

void sigint_handler(int sig)
{
    printf("Caught SIGINT\n");
    return;
}

int main()
{
    /* install sigint handler */
    if((signal(SIGINT,sigint_handler))==SIG_ERR)
    {
        perror("signal error");
    }
    pause();  /* wait for the receipt of a signal */
    printf("hey\n");  //in handler if you use return it will resume printf her , but if you use exit it will not
    return 0;
}