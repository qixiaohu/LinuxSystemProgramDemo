#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int count=100;

int main()
{
    int number=5;
    int i=0;
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
        count+=100;
        printf("I am the %d child process,pid = %d,ppid = %d\n",i,getpid(),getppid());
    }
    if(i==number)
    {
        count+=1;
        printf("I am the parent process,pid = %d,ppid = %d\n",getpid(),getppid());
        sleep(1);
    }

    return 0;

}
