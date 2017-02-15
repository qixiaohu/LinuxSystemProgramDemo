#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc,const char *argv[])
{
    int fd=open("fifo",O_WRONLY);
    if(fd==-1)
    {
        perror("open error");
        exit(1);
    }
    char *str="Hello,World.....";
    int strlen1=strlen(str);
    int len=write(fd,str,strlen1);
    printf("write:%s,len:%d\n",str,len);
    close(fd);
}

