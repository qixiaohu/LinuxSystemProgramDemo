#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void)
{
    pid_t pid;
    char *message;
    int n;
    pid=fork();
    if(pid==-1)
    {
        perror("fork failed");
        exit(0);
    }
    if(pid==0)
    {
        message="This is the child";
        n=6;
    }
    else
    {
        message="This is the patent";
        n=3;
    }

    for(;n>0;n--)
    {
        printf("%s",message);
        printf("    pid:%d\n\n",getppid());
        sleep(1);
    }

    return 0;
}
