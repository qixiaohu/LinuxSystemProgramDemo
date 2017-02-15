#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <string.h>
#include "wrap.h"
#include <pthread.h>

#define pNum 10

typedef struct info
{
    int fd;
    struct sockaddr_in sock_addr;
}Info;

void *my_func(void *arg)
{
    Info *info=(Info *)arg;
    char msgBuf[1024]={0};
    char buf[128]={0};
    inet_ntop(AF_INET,&info->sock_addr.sin_addr.s_addr,buf,sizeof(buf)) ;
    printf("----Client IP:%s----Client Port:%d----\n",buf,ntohs(info->sock_addr.sin_port));
    while(1)
    {
        int rlen=read(info->fd,msgBuf,sizeof(msgBuf));
        if(rlen==0)
        {
            printf("Read buf is empty,Exit!\n");
            break;
        }
        printf("recv:%s\n",msgBuf);
        for(int i=0;i<rlen;i++)
        {
            msgBuf[i]=toupper(msgBuf[i]);
        }
        printf("send:%s\n",msgBuf);
        write(info->fd,msgBuf,sizeof(msgBuf));
    }
    close(info->fd);
    return (void *)0;
}

int main(int argc,const char *argv[])
{
    int i=0;
    int sfd=Socket(AF_INET,SOCK_STREAM,0);

    //服务器端套接字
    struct sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    server_addr.sin_port=htons(9999);

    Bind(sfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
    Listen(sfd,64);

    //链接至服务器的客户端套接字
    struct sockaddr_in client_addr;
    client_addr.sin_family=AF_INET;
    socklen_t sock_len=sizeof(client_addr);

    Info pUser[pNum];

    while(1)
    {
        int afd=Accept(sfd,(struct sockaddr *)&client_addr,&sock_len);

        pUser[i] .fd=afd;
        pUser[i].sock_addr=client_addr;

        pthread_t pthid;
        int ret=pthread_create(&pthid,NULL,my_func,(void *)&pUser[i]);
        if(ret!=0)
        {
            printf("pthread_create error:%s\n",strerror(ret));
            exit(0);
        }
        pthread_detach(pthid);
        i++;
        if(i==pNum)
        {
            break;
        }
    }
    return 0;
}
