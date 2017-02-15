#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/stat.h>
int main()
{
    int i=0;
    int number=5;
    for( i=0;i<number;i++)
    {
        pid_t pid=fork();
        if(pid==0)
        {
            break;
        }
    }
    if(i<number)
    {
        printf("I am the child process,pid = %d,ppid = %d!\n",getpid(),getppid());
    }

    if(i==number)
    {
        int status;
        pid_t wpid;
        while((wpid=wait(&status))!=-1)
        {
            if(WIFEXITED(status))
            {
                printf("process exit by number:%d\n",WEXITSTATUS(status));
            }
            else if(WIFSIGNALED(status))
            {
                printf("process kill by signal:%d\n",WTERMSIG(status));
            }
            printf("child died pid = %d\n",wpid);
        }
    }
    
    return 10;

    return 0;
}
