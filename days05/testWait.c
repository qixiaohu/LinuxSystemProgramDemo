#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>

int main()
{
    int i=0;
    int number=5;

    for(i=0;i<number;i++)
    {
        pid_t pid=fork();
        if(pid==0)
        {
            break;
        }
    }

    if(i<number)
    {
        printf("I am the child process,pid = %d,ppid = %d\n",getpid(),getppid());
        sleep(100);

    }

    if(i==number)
    {
        int status;
        pid_t wpid;
        while((wpid=wait(&status))!=-1)
        {
            //正常退出
            if(WIFEXITED(status))
            {
                printf("process exit by number:%d\n",WEXITSTATUS(status));
            }
            if(WIFSIGNALED(status))
            {
                printf("process kill by number:%d\n",WTERMSIG(status));
            }
        }
    }
    return 100;
}
