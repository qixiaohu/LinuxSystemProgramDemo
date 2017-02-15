#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

void my_func(int num)
{
    printf("catch you signal:%d\n",num);
//    sleep(5);
//    printf("wake up=========\n");
}

int main(int argc,const char *argv[])
{
    struct sigaction sigact;
    sigact.sa_flags=0;   //表示使用默认属性
    sigemptyset(&sigact.sa_mask);

    sigaddset(&sigact.sa_mask,SIGQUIT);


    sigprocmask(SIG_BLOCK,&sigact.sa_mask,NULL); 

    sigact.sa_handler=my_func;

    int ret=sigaction(SIGINT,&sigact,NULL);
    if(ret==-1)
    {
        perror("sigaction error");
        exit(0);
    }

    sigset_t myset;

    while(1)
    {
        sigpending(&myset);
        for(int i=1;i<32;i++)
        {
            if(sigismember(&myset,i))
            {
                printf("1");
            }
            else
            {
                printf("0");
            }
        }
        sleep(1);
        printf("\n");
    }
}
