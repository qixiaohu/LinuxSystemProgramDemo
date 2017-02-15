#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


int main(int argc, const char* argv[])
{
    pid_t pid;
    pid = fork();

    if(pid == -1)
    {
        perror("fork error");
        exit(1);
    }

    if(pid > 0)
    {
        exit(1);
        // kill raise abort
    }
    else if(pid == 0)
    {
        // 子进程提升为会长
        setsid();
        while(1);
    }
    return 0;
}
