#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc,const char*argv[])
{
    int fd=open("mmap.txt",O_RDWR|O_CREAT,0664);
    void *ptr=mmap(NULL,1,PROT_READ|PROT_WRITE,MAP_PRIVATE,fd,0);
    if(ptr==MAP_FAILED)
    {
        printf("内存映射区创建失败！");
        exit(0);
    }
    sleep(10);
    char buf[1024]={0};
    strcpy(buf,ptr);
    printf("%s\n",buf);
    close(fd);
}
