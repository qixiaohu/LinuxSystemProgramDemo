#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


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
    pid_t pid = fork();
    if(pid == -1)
    {
        perror("fork error");
        exit(1);
    }
    // 3. 通信
    // 父进程 写操作
    // 子进程 读操作
    if(pid > 0)
    {
        // parent process
        // 关闭读端
        close(fd[0]);
        char* p = "你是我失散多年的孩子吗？";
        sleep(2);
        write(fd[1], p, strlen(p)+1);
        close(fd[1]);

        wait(NULL);
    }
    else if(pid == 0)
    {
        // 关闭写端
        close(fd[1]);
        char buf[512];
        int len = read(fd[0], buf, sizeof(buf));
        printf("%s, %d\n", buf, len);
        close(fd[0]);
    }
    return 0;
}
