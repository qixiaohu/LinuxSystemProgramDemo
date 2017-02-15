#include <stdio.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h> 
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc,const char *argv[])
{
    int fd[2];
    int ret=pipe(fd);
    if(ret==-1)
    {
        perror("pipe error");
        exit(1);
    }
    pid_t pid=fork();
    if(pid==-1)
    {
        perror("fork error");
        exit(1);
    }
    //子进程read
    if(pid==0)
    {
        close(fd[1]);
        char buf[512]={0};
        //设置管道的read断不再阻塞
      //  int flag=fcntl(fd[0],F_GETFL);
      //  flag|=O_NONBLOCK;
      //  fcntl(fd[0],F_SETFL,flag);
        int len=read(fd[0],buf,sizeof(buf));
        printf("info:%s,len:%d\n",buf,len);
        close(fd[0]);
    }
    //父进程write
    if(pid>0)
    {
        close(fd[0]);
//        sleep(2);
    //    write(fd[1],"HelloWorld!-----------",100);
        sleep(10);
        close(fd[1]);
    }

    return 0;
}
