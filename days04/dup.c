#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    int fd1=open("aaa.txt",O_RDONLY);
    printf("fd1:%d\n",fd1);

    int fd2=dup(fd1);

    close(fd1);

    printf("df2:%d\n",fd2);

    int fd3=dup(fd2);
    printf("fd3:%d\n",fd3);
   
    close(fd2);
    close(fd3);

    return 0;
}

