#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <sys/epoll.h>

#define OPEN_MAX 1024

int main(int argc,const char *argv[])
{
    int num=0;
    int sfd=socket(AF_INET,SOCK_STREAM,0);
    if(sfd==-1)
    {
        perror("socket error");
    }

    //构造服务器端套接字
    struct sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    server_addr.sin_port=htons(8989);

    //绑定
    int bret=bind(sfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
    if(bret==-1)
    {
        perror("bind error");
        exit(0);
    }

    //开启监听功能
    int lret=listen(sfd,64);
    if(lret==-1)
    {
        perror("lret error");
        exit(0);
    }

    //创建epoll红黑树

    int epfd=epoll_create(OPEN_MAX);
    if(epfd==-1)
    {
        perror("epoll_create error");
        exit(0);
    }

    //把用于监听的文件描述符添加到红黑树上
    //构造监听的文件描述符的结构体
    struct epoll_event tempep;
    tempep.events=EPOLLIN;
    tempep.data.fd=sfd;
    int ep_ctl=epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&tempep);
    if(ep_ctl==-1)
    {
        perror("epoll_ctl error");
        exit(0);
    }

    //客户端套接字
    struct sockaddr_in client_addr;
    socklen_t client_len=sizeof(client_addr);

    //构造epoll_wait函数函数的参数
    struct epoll_event events[OPEN_MAX];
    char buf[1024]={0};
    char str[16]={0};

    while(1)
    {
        int nready=epoll_wait(epfd,events,OPEN_MAX,-1);
        if(nready==-1)
        {
            perror("epoll_wait error");
            exit(0);
        }
        for(int i=0;i<nready;i++)
        {
            if(!(events[i].events&EPOLLIN))
            {
                continue;
            }
            if(events[i].data.fd==sfd)
            {
                int afd=accept(sfd,(struct sockaddr *)&client_addr,&client_len);
                if(afd==-1)
                {
                    perror("accept error");
                    exit(0);
                }
                printf("----client IP:%s----client PORT:%d----\n",inet_ntop(AF_INET,&client_addr.sin_addr,str,sizeof(str)),ntohs(client_addr.sin_port));
                printf("cfd %d----client%d\n",afd,++num);

                tempep.events=EPOLLIN;
                tempep.data.fd=afd;

                int res=epoll_ctl(epfd,EPOLL_CTL_ADD,afd,&tempep);
                if(res==-1)
                {
                    perror("epoll_ctl error");
                    exit(0);
                }
            }

            //处理用户的读操作
            else
            {
                int sockfd=events[i].data.fd;
                int len=read(sockfd,buf,sizeof(buf));
                if(len==-1)
                {
                    perror("read error");
                    exit(0);
                }
                else if(len==0)
                {
                    int res1=epoll_ctl(epfd,EPOLL_CTL_DEL,sockfd,NULL);
                    if(res1==-1)
                    {
                        perror("epoll_ctl error");
                        exit(0);
                    }
                    close(sockfd);
                    printf("client [%d] closed connection\n",sockfd);
                }
                else
                {
                    printf("recv:%s\n",buf);
                    for(int i=0;i<len;i++)
                    {
                        buf[i]=toupper(buf[i]);
                    }
                    printf("send:%s\n",buf);
                    write(sockfd,buf,strlen(buf)+1);
                }
            }
        }
    }
    close(sfd);
    return 0;
}
