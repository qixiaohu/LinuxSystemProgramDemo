#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc,const char *argv[])
{
    pid_t fd[2];
    int ret=pipe(fd);
    if(ret==-1)
    {
        perror("pipe error");
        exit(0);
    }

    int i=0;
    int number=2;
    pid_t pid;
    for( i=0;i<number;i++)
    {
        pid=fork();
        if(pid==-1)
        {
            perror("fork error");
            exit(0);
        }
        if(pid==0)
        {
            break;
        }
    }
    //子进程1，write
    if(i==0)
    {
        close(fd[0]);
        printf("I am the first child,my pid:%d,ppid:%d\n",getpid(),getppid());
        int ret=dup2(fd[1],1);
        if(ret==-1)
        {
            perror("dup2 error");
            exit(0);
        }
        execlp("ps","ps","aux",NULL);
        perror("execlp error");
        exit(0);
    }
    if(i==1)
    {
        close(fd[1]);
        printf("I am the second child,my pid:%d,ppid:%d\n",getpid(),getppid());
        int ret=dup2(fd[0],0);
        if(ret==-1)
        {
            perror("dup2 error");
            exit(0);
        }
        execlp("grep","grep","bash",NULL);
        perror("execlp error");
        exit(0);
    }
    if(i==2)
    {
        close(fd[0]);
        close(fd[1]);
        printf("I am the parent process,pid:%d,ppid:%d\n",getpid(),getppid());
        pid_t wpid;
        int status;
        while((wpid=wait(&status))!=-1)
        {
            if(WIFEXITED(status))
            {
                printf("child process is died by:%d,pid:%d\n",WEXITSTATUS(status),wpid);
            }
            if(WIFSIGNALED(status))
            {
                printf("child process is died by:%d,pid:%d\n",WEXITSTATUS(status),wpid);
            }
        }
    }
}

