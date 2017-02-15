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
    ftruncate(fd,1024);
    void *ptr=mmap(NULL,1,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(ptr==MAP_FAILED)
    {
        printf("内存映射区创建失败！");
        exit(0);
    }
    char *str="99999999999999999999999999999999999999";
    strcpy(ptr,str);
    close(fd);
}
