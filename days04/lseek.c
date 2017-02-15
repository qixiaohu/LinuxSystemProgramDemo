#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    int fd=open("aaa.txt",O_RDWR);
    int len=(int)lseek(fd,0,SEEK_END);
    printf("size:%d\n",len);


    lseek(fd,1000,SEEK_END);
    write(fd,"a",1);
    int len1=(int)lseek(fd,0,SEEK_END);
    printf("size:%d\n",len1);

    return 0;
}

