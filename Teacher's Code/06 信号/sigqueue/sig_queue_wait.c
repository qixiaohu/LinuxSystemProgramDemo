#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void new_op(int signum,siginfo_t *info,void *myact)
{
    printf("\n==================================\n");
    printf("****** catch you signal: %d\n", signum);
    printf("****** the int value is %d \n",info->si_int);
    printf("\n==================================\n");
}

int main(int argc,char**argv)
{
    struct sigaction act;

    sigemptyset(&act.sa_mask);
    act.sa_sigaction = new_op;
    act.sa_flags = SA_SIGINFO;

    if(sigaction(SIGINT, &act, NULL)<0)
    {
        printf("install sigal error\n");
    } 

    while(1)
    {
        sleep(1);
        printf("wait for the signal\n");
    }
} 
