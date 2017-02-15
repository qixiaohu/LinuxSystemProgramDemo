#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc,const char *argv[])
{
    int fd[2];
    int ret=pipe(fd);
    if(ret==-1)
    {
        perror("pipe error");
        exit(1);
    }

    long size= sizefpathconf(fd[0],_PC_PIPE_BUF);

    printf("size = %ld\n",size);

}
