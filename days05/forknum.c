#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int pid=fork();

    for(int i=0;i<5;i++)
    {
        if(pid==0)
        {
            break;
        }
        printf("我是第%d个子进程,我的父进程id=%d!\n",i,getppid());
    }

    return 0;
}
