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
    //int len=ftruncate(fd,1024);
    //if(len==-1)
    //{
    //    perror("truncate error");
    //    exit(0);
    //}
    void *ptr=mmap(NULL,1,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(ptr==MAP_FAILED)
    {
        printf("内存映射区创建失败！");
        exit(0);
    }
    pid_t pid=fork();
    if(pid==0)
    {
        sleep(2);
        char buf[1024]={0};
        strcpy(buf,ptr);
        printf("%s\n",buf);
    }
    else if(pid>0)
    {
        char buf[]={'a','b','c','d','e','f','g','h','i','\0'};
        strcpy(ptr,buf);
        sleep(1);
       // printf("%s\n",(char *)ptr);
    }

    close(fd);


}
