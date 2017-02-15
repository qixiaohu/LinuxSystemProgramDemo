#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <string.h>

#define MAX_LINE 10
#define OPEN_MAX 5

int main(int argc,const char *argv[])
{
    int pfd[2];
    pid_t pid;
    char buf[MAX_LINE]={0};
    char ch='a';

    pipe(pfd);
    pid=fork();
    if(pid==0)
    {
        close(pfd[0]);
        while(1)
        {
            int i=0;
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
            printf("===================\n");
            printf("%s\n",buf);
            sleep(3);
        }
        close(pfd[0]);
    }
    if(pid>0)
    {
        close(pfd[1]);

        //构造红黑树
        int epfd=epoll_create(OPEN_MAX);

        //构造父进程的读的epoll_event结构体
        struct epoll_event event;
        event.data.fd=pfd[0];
        event.events=EPOLLIN|EPOLLET;

        //构造epoll_wait函数的参数
        struct epoll_event fds[OPEN_MAX];

        //把父进程读的文件描述符挂到红黑树上
        epoll_ctl(epfd,EPOLL_CTL_ADD,pfd[0],&event);

        while(1)
        {
            int nready=epoll_wait(epfd,fds,OPEN_MAX,-1);
            for(int i=0;i<nready;i++)
            {
                if(!(fds[i].data.fd==pfd[0]))
                {
                    continue;
                }
                if(fds[i].data.fd==pfd[0])
                {
                    read(fds[i].data.fd,buf,MAX_LINE/2);
                    printf("read buf:%s\n",buf);
                }
            }
            sleep(1);
        }
    }
    close(pfd[0]);
    return 0;
}
