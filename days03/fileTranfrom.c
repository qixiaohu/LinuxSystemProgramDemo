#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> 
#include <string.h>

int main(int argc,char *argv[])
{
    char buf[20]={0};

    int fd1=open("stdio.h",O_RDONLY);
    int fd2=open("aaa.txt",O_WRONLY|O_CREAT|O_EXCL,0664);

    while(read(fd1,buf,sizeof(buf)))
    {
        printf("%s",buf);
        int len  = strlen(buf);
        write(fd2,buf,len);
        memset(buf,0,20);
    }
    close(fd1);
    close(fd2);
}
