#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


int main(int argc, const char* argv[])
{
    int fd[2];
    int ret = pipe(fd);
    if(ret == -1)
    {
        perror("pipe error");
        exit(1);
    }

    long size = fpathconf(fd[0], _PC_PIPE_BUF);
    printf("size = %ld\n", size);
    size = fpathconf(fd[1], _PC_PIPE_BUF);
    printf("size = %ld\n", size);
    return 0;
}
