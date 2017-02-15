#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{

    if(argc<2)
    {
        printf("a.out filename\n");
    }

    int ret=chmod("aaa.txt",0777);
    if(ret==-1)
    {
        perror("chmod");
        exit(0);
    }

    printf("权限修改成功");
}
