#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <string.h>
#include "wrap.h"
#include <errno.h>
#include <pthread.h>
#include <sys/socket.h>

#define pNum 10

typedef struct info
{
    int pthid;
    struct sockaddr_in sock_addr;
}Info;


void *my_func(void *arg)
{
    Info *info=(Info *)arg;
    char buf[128]={0};
    inet_ntop(AF_INET,&(info->sock_addr.sin_addr.s_addr),buf,sizeof(buf));
    printf("----Client IP:%s----client Port:%d----\n",buf,ntohs(info->sock_addr.sin_port));

    char msgBuf[1024]={0};
        
    while(1)
    {
        int rlen= read(info->pthid,msgBuf,sizeof(msgBuf));
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
        printf("rend:%s\n",msgBuf);
        write(info->pthid,msgBuf,sizeof(msgBuf));
    }           
    close(info->pthid);
    return (void *)0;
}

int main(int argc,const char *argv[])
{
    int i=0;
    Info pUser[pNum];
    //创建用于监听的套接字
    int sfd=Socket(AF_INET,SOCK_STREAM,0);

    //服务器端套接字
    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    server_addr.sin_port=htons(9999);

    //绑定与监听
    Bind(sfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
    Listen(sfd,64);

    //接入服务器的客户端的套接字
    struct sockaddr_in client_addr;
    bzero(&client_addr,sizeof(client_addr));
    client_addr.sin_family=AF_INET;
    socklen_t sock_len=sizeof(client_addr);

    int afd;
    while(1)
    {
        afd=accept(sfd,(struct sockaddr *)&client_addr,&sock_len);
        if(afd<0)
        {
            if(errno==ECONNABORTED||errno==EINTR)
            {
                continue;
            }
            else
            {
                exit(0);
            }
        }
        
        pUser[i].pthid=afd;
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
}
