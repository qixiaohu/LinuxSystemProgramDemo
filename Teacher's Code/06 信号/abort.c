#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, const char* argv[])
{
    pid_t pid = fork();
    if(pid == -1)
    {
        perror("fork error");
        exit(1);
    }

    if(pid > 0)
    {
        // parent process
        // recyle child pcb
        int status;
        pid_t wpid = wait(&status);
        printf("===== child pid = %d\n", wpid);
        if(WIFSIGNALED(status))
        {
            printf("kill by signal: %d\n", WTERMSIG(status));
        }
    }
    else if(pid == 0)
    {
        sleep(1);
        abort();
    }
    return 0;
}
