#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int ret=chdir("/home/itheima/");

    if(ret==-1)
    {
        perror("chdir");
        exit(0);
    }

    int fd=open("TEST.TXT",O_RDWR|O_CREAT,0777);
    if(fd==-1)
    {
        perror("open");
        exit(0);
    }


    printf("创建成功 ！");

    return 0;
}
