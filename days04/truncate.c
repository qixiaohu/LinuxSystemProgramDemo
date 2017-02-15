#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    if(argc<3)
    {
        printf("a.out filename length\n");
        exit(0);
    }


    int length=atoi(argv[2]);

    int ret=truncate(argv[1],length);
    


    if(ret==-1)
    {
        perror("truncate");
        exit(0);
    }

    printf("扩展成功！");

    return 0;
}
