#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    int ret=rmdir("test");

    if(ret==-1)
    {
        perror("rmdir");
        exit(0);
    }
    printf("删除成功");

    return 0;
}

