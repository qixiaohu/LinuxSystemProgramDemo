#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    if(argc<2)
    {
        printf("a.out filename\n");
        exit(0);
    }
    int ret=(int)chown("aaa.txt",1000,1000);

    if(ret==-1)
    {
        perror("chown");
        exit(0);
    }

    printf("修改成功!\n"); 
}
