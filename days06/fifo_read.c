#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc,const char *argv[])
{
    int fd=open("fifo",O_RDONLY);
    if(fd==-1)
    {
        perror("open error");
        exit(0);
    }
    char buf[1024]={0};
    int len=read(fd,buf,sizeof(buf));
    printf("read:%s,len:%d\n",buf,len);
    close(fd);

    return 0;
}
