#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc,char *argv[])
{
    if(argc<2)
    {
        printf("a.out filename\n");
        exit(0);
    }
    struct stat stat_buf;
    int ret=lstat(argv[1],&stat_buf) ;
    if(ret==-1)
    {
        perror("stat");
        exit(0);
    }
    printf("file size:%d\n",(int)stat_buf.st_size);

    return 0;
}

