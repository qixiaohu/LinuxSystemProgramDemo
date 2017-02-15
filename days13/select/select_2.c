#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <ctype.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>

int main(int argc,const char *argv[])
{
    int sfd=socket(AF_INET,SOCK_STREAM,0);
    if(sfd==-1)
    {
        perror("socket error");
        exit(-1);
    }

    //服务器端套接字
    struct sockaddr_in server_addr;
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    server_addr.sin_port=htons(9999);

    //绑定
    int bret=bind(sfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
    if(bret==-1)
    {
        perror("bind error");
        exit(-2);
    }

    //开启监听
    int lret=listen(sfd,64);
    if(lret==-1)
    {
        perror("listen error");
        exit(-3);
    }

    //构造select监控文件描述符表
    int maxfd=sfd;

    fd_set test,reads;
    FD_ZERO(&reads);
    FD_SET(sfd,&reads);

    //服务器开始循环select
    while(1)
    {
        test=reads;
        //maxfd+1为设置select监听的文件描述符范围
        int sret=select(maxfd+1,&test,NULL,NULL,NULL);
        if(sret==-1)
        {
            perror("select error");
            exit(-3);
        }

        //客户端的套接字
        struct sockaddr_in client_addr;
        client_addr.sin_family=AF_INET;
        socklen_t sock_len=sizeof(client_addr);

        //检测是否有新的客户端链接至服务器,即检测用于监听的文件描述符是否发生了IO操作
        if(FD_ISSET(sfd,&test))
        {
            int afd=accept(sfd,(struct sockaddr *)&client_addr,&sock_len);
            if(afd==-1)
            {
                perror("accept error");
                exit(0);
            }
            //将获取的客户端的文件描述符添加到监控列表
            FD_SET(afd,&reads);

            maxfd=maxfd<afd?afd:maxfd;
        }

        //处理客户端的读操作
        for(int i=sfd+1;i<=maxfd;i++)
        {
            char msgBuf[1024]={0};
            if(FD_ISSET(i,&test))
            {
                int len=recv(i,msgBuf,sizeof(msgBuf),0);
                if(len==-1)
                {
                    perror("recv error");
                    exit(-4);
                }
                else if(len==0)     //客户端的写端被关闭，服务端读0
                {
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
