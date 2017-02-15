#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>


int main(int argc, const char* argv[])
{
    int fd = open("english.txt", O_RDWR);
    if(fd == -1)
    {
        perror("open error");
        exit(1);
    }
    void* ptr = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(ptr == MAP_FAILED)
    {
        perror("mmap error");
        exit(1);
    }
    close(fd);

    printf("buf = %s\n", (char*)ptr);
    // 修改映射区数据
    strcpy(ptr, "99999999999999999999999999999999999999999999");


    // 释放内存映射区
    int ret = munmap(ptr, 1024);
    if(ret == -1)
    {
        perror("munmap error");
        exit(1);
    }
    return 0;
}
