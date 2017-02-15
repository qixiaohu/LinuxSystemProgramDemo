#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

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
        exit(1);
    }
    else if(pid == 0)
    {
        // 提升为会长，也成为了组长
        setsid();
        // 改变工作路径
        chdir("/home/kevin");
        // 修改掩码
        umask(0022);
        // 关闭文件描述符
        close(0);
        close(1);
        close(2);

        // 守护进程处理操作
        while(1)
        {
            // xxxxxx
            int fd = open("/home/kevin/temp", O_RDWR | O_CREAT | O_APPEND,  0664);
            char* p = "hello, world...\n";
            write(fd, p, strlen(p)+1);
            close(fd);
            sleep(2);
        }
    }
    return 0;
}
