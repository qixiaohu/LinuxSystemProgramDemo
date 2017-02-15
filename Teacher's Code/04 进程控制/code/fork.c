#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{
    pid_t pid;

    pid = fork();

    // 父进程
    if(pid > 0)
    {
        printf("i am parent porcess\n");
    }
    else if(pid == 0)
    {
        // 子进程
        printf("i am child process\n");
    }

    for(int i=0; i<5; ++i)
    {
        printf(" i = %d\n", i);
    }

    return 0;
}
