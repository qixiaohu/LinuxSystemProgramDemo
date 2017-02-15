#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, const char* argv[])
{
    // 1. 创建管道
    int fd[2];
    int ret = pipe(fd);
    if(ret == -1)
    {
        perror("pipe error");
        exit(1);
    }

    // 2. 创建子进程
    pid_t pid;
    int i;
    for(i=0; i<2; ++i)
    {
        pid = fork();
        if(pid  == 0)
        {
            break;
        }
        if(pid == -1)
        {
            perror("fork error");
            exit(1);
        }

    }
    // 父进程：回收子进程
    // 子1进程： ps aux -- 写操作
    // 子2进程： grep bash -- 读操作
    if(i == 0)
    {
        // g关闭读端
        close(fd[0]);
        // 重定向 标准输出 -- 》管道的写端
        dup2(fd[1], STDOUT_FILENO);
        execlp("ps", "ps", "aux", NULL);
        perror("execlp ps aux");
        exit(1);
    }
    else if(i == 1)
    {
        // 关闭写端
        close(fd[1]);
        // 重定向： 标准输入  -》 管道的读端
        dup2(fd[0], STDIN_FILENO);
        execlp("grep", "grep", "bash", NULL);
        perror("execlp grep bash");
        exit(1);
    }
    else if(i == 2)
    {
        // 保证数据单向流动
        close(fd[0]);
        close(fd[1]);

        pid_t wpid;
        while( (wpid = wait(NULL)) != -1 )
        {
            printf("--------------child pid = %d\n", wpid);
        }
    }
    return 0;
}
