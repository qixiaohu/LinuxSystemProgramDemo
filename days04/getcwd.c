#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    char buf[1024];

    char *pathname=NULL;
    pathname=getcwd(buf,sizeof(buf));

    if(pathname==NULL)
    {
        perror("getcwd");
        exit(0);
    }

    printf("获取成功！\n");
    printf("workSpace:%s\n",pathname);
    printf("buf:%s\n",buf);
    return 0;

}

