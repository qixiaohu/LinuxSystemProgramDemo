#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

int main()
{
    pid_t pid=fork();
    if(pid==-1)
    {
        perror("fork error");
        exit(0);
    }
    if(pid==0)
    {
        execlp("ps","abcde","aux",NULL);
        perror("execl error");
        exit(0);
    }
    else if(pid>0)
    {
        printf("Hello World!\n");
        sleep(1);
    }
    return 0;
}
