#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
    int fdr=open("stdio.h",O_RDONLY);
    if(fdr==-1)
    {
        perror("open error");
        exit(0);
    }
    int fdw=open("aaa.txt",O_WRONLY|O_CREAT|O_EXCL,0664);
    if(fdw==-1)
    {
        close(fdw);
        fdw=open("aaa.txt",O_WRONLY|O_CREAT,0664);
    }

    char buf[BUFSIZ];
    int len=read(fdr,buf,sizeof(buf));
    while(len>0)
    {
        int count=write(fdw,buf,len);
        len=read(fdr,buf,sizeof(buf));
        printf("count:%d\n",count);
    }

    close(fdr);
    close(fdw);

    return 0;
}
