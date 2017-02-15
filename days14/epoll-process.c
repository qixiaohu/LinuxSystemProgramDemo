#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <ctype.h>
#include <sys/epoll.h>

#define MAX_LINE 10

int main(int argc,const char *argv[])
{
    //匿名管道
    int pfd[2];
    pipe(pfd);
    char buf[MAX_LINE];

    char ch='a';

    pid_t pid=fork();
    if(pid==0)
    {
        close(pfd[0]);
        int i=0;
        //子   写
        while(1)
        {
            for(i=0;i<MAX_LINE/2;i++)
            {
                buf[i]=ch;
            }
            buf[i-1]='\n';
            ch++;
            for(;i<MAX_LINE;i++)
            {
                buf[i]=ch;
            }
            buf[i-1]='\n';
            ch++;
            write(pfd[1],buf,sizeof(buf));
            printf("===========\n");
            printf("%s\n",buf);

            sleep(3);
        }
        close(pfd[0]);
    }
    else if(pid>0)
    {
        //父   读
        close(pfd[1]);

        int epfd=epoll_create(1);

        //父进程读取管道的文件描述符的epoll结构体
        struct epoll_event event;

        //构造epoll_wait函数的参数
        struct epoll_event fds[1];
        //边缘模式时，如果一次读不完，会造成缓冲区内的信息越来越多【管道】
        event.events=EPOLLIN|EPOLLET;
        event.data.fd=pfd[0];

        epoll_ctl(epfd,EPOLL_CTL_ADD,pfd[0],&event);

        while(1)
        {
            int ret1=epoll_wait(epfd,fds,1,-1) ;
            if(fds[0].data.fd==pfd[0])
            {
                printf("num:%d\n",ret1) ;
                int len= read(fds[0].data.fd,buf,MAX_LINE/2);
                write(STDOUT_FILENO,buf,len);
            }
        }        
    }
    close(pfd[0]);
    return 0;
}
