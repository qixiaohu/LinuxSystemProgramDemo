#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t pid;
    pid=fork();
    if(pid<0)
    {
        perror("fork error:");
        exit(0);
    }
    if(pid==0)
    {
        printf("I am the child process.\n");
        printf("pid:%d\tppid:%d\n",getpid(),getppid());
        printf("I will sleep five seconds.\n");

        sleep(5);

        printf("pid:%d\tppid:%d\n",getpid(),getppid());
        printf("child process is exited.\n");
    }

    else
    {
        printf("I am father process.\n");
        sleep(1);
        printf("father process is exit.\n");
    }

    return 0;
}
