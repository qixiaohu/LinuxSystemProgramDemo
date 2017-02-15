#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>


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
        sleep(100);
        exit(9);
    }
    else if(i == number)
    {
        counter += 300;
        printf("parent pid = %d, ppid = %d\n", getpid(), getppid());
        printf("counter = %d\n\n", counter);
        sleep(1);

        // 回收子进程
        int status;
        pid_t wpid;
        while( (wpid=wait(&status)) != -1)
        {
            // 正常退出
            if(WIFEXITED(status))
            {
                printf("porcess exit by number: %d\n", WEXITSTATUS(status));
            }
            // 被信号杀死
            else if(WIFSIGNALED(status))
            {
                printf("process kill by signal: %d\n", WTERMSIG(status));
            }
            printf("child died pid = %d\n", wpid);
        }
    }
    return 10;
}
