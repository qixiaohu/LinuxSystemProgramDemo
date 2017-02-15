#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,const char *argv[])
{
    pid_t fd[2];
    int ret=pipe(fd);
    if(ret==-1)
    {
        perror("pipe error");
        exit(0);
    }
    pid_t pid=fork();
    if(pid==-1)
    {
        perror("fork error");
        exit(0);
    }
    //子进程，write
    if(pid==0)
    {
        close(fd[0]);
        int ret=dup2(fd[1],1);
        if(ret==-1)
        {
            perror("dup2 error");
            exit(1);
        }
        execlp("ps","ps","aux",NULL);
        perror("execlp error");
        exit(1);
    }
    //父进程,read
    if(pid>0)
    {
        close(fd[1]);
        int ret=dup2(fd[0],0);
        if(ret==-1)
        {
            perror("dup2 error");
            exit(1);
        }
        execlp("grep","grep","bash",NULL);
        perror("execlp error");
        exit(0);
    }
    return 0;
}
