#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    int ret=mkdir("/home/itheima/aaaaaaa",0777);
    if(ret==-1)
    {
        perror("mkdir");
        exit(0);
    }

    printf("创建成功!");

    return 0;
}
