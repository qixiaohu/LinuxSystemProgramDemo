#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    int fd1=open("aaa.txt",O_RDONLY);
    int fd2=open("dup.c",O_RDONLY);
    printf("fd2:%d\n",fd2);

    int fd3=dup2(fd1,fd2);``

    printf("fd1:%d\n",fd1);
    printf("fd3:%d\n",fd3);
    printf("fd1:%d\n",fd1);
}
