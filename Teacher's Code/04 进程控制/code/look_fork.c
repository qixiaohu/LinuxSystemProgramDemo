#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


int counter = 100;

int main(int argc, const char* argv[])
{
    int number = 5;

    int i;
    pid_t pid;

    for(i=0; i<number; ++i)
    {
        pid = fork();
        if(pid == 0)
            break;
    }

    if(i<number)
    {
        // 子进程
        counter += 100;
        printf("child pid = %d, ppid = %d\n", getpid(), getppid());
        printf("counter = %d\n\n", counter);
    }
    else if(i == number)
    {
        counter += 300;
        printf("parent pid = %d, ppid = %d\n", getpid(), getppid());
        printf("counter = %d\n\n", counter);
        sleep(1);
    }
    

    return 0;
}
