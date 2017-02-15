#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <ctype.h>

#define SERV_PORT 9999
int main(int argc,const char *argv[]) 
{
    int sfd,afd,maxfd;
    struct sockaddr_in server_addr,client_addr;
    int bret,lret,sret;
    fd_set test,reads;
    sfd=socket(AF_INET,SOCK_STREAM,0);

    if(sfd==-1)
    {
        perror("socket error") ;
        exit(0);
    }
    //客户端套接字
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    server_addr.sin_port=htons(SERV_PORT);

    //绑定
    bret=bind(sfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
    if(bret==-1)
    {
        perror("bind error");
        exit(0);
    }
    lret=listen(sfd,64);
    if(lret==-1)
    {
        perror("listen error");
        exit(0);
    }
    //将监听文件描述符添加到select监控列表
    maxfd=sfd;
    FD_ZERO(&reads);
    FD_SET(sfd,&reads);
    while(1)
    {
        test=reads;
        //select监控的是表上的一个区间，是左闭右开的，所以最后一位要写到+1
        sret=select(maxfd+1,&test,NULL,NULL,NULL);
        if(sret==-1)
        {
            perror("select error");
            exit(0);
        }
        //检测是否有新的用户连如服务器
        if(FD_ISSET(sfd,&test))
        {
            client_addr.sin_family=AF_INET;
            socklen_t sock_len=sizeof(client_addr);
            afd=accept(sfd,(struct sockaddr *)&client_addr,&sock_len);
            if(afd==-1)
            {
                perror("accept error");
                exit(0);
            }
            FD_SET(afd,&reads);
            maxfd=maxfd<afd?afd:maxfd;
        }
        //处理客户端的写操作
        for(int i=sfd+1;i<=maxfd;i++)
        {
            char msgBuf[1024]={0};
            if(FD_ISSET(i,&test))
            {
                int len=recv(i,msgBuf,sizeof(msgBuf),0);
                if(len==-1)
                {
                    printf("recv error");
                    exit(0);
                }
                else if(len==0)
                {
                    //写端关闭，服务端读0
                    printf("The client is exit!\n");
                    FD_CLR(i,&reads);
                    close(i);

                }
                else
                {
                    printf("recv:%s\n",msgBuf);
                    for(int j=0;j<len;j++)
                    {
                        msgBuf[j]=toupper(msgBuf[j]);
                    }
                    send(i,msgBuf,strlen(msgBuf)+1,0);
                    printf("send:%s\n",msgBuf);
                }
            }
        }

    }
    close(sfd);
    return 0;
}
