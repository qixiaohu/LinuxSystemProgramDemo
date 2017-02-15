#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
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
        //sleep(1);
        printf("I am the child process,pid = %d,ppid = %d!\n",getpid(),getppid());
    }

    if(i==number)
    {
        printf("%s\n","4444444444444444444444");
        while(1)
        {
            printf("%s\n","!!!!!!!!!!!!!!!!!!!!!!!!!!");
            sleep(1);
        }
        printf("I am the parent process,pid = %d,ppid = %d!\n",getpid(),getppid());
        //sleep(1);
    }
    return 0;
}
