#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


int main(int argc, const char* argv[])
{
    pid_t pid = fork();
    if(pid == -1)
    {
        perror("fork error");
        exit(1);
    }

    // 子进程执行ls -lha
    if(pid == 0)
    {
//      execl("/bin/ls", "ls", "-lha", NULL);
        execlp("ps", "abcd", "aux", NULL);
        printf("hello, ls=============\n");
        perror("execlp");
        exit(1);
    }
    printf("hello, world.....\n");
    sleep(1);
    return 0;
}
