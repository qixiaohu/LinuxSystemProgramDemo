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
#include <poll.h>
#include <ctype.h>

#define SERV_PORT 8989

int main(int argc,const char *argv[])
{
    int sfd=socket(AF_INET,SOCK_STREAM,0);
    if(sfd==-1)
    {
        perror("socket error") ;
        exit(0);
    }

    //服务器端套接字
    struct sockaddr_in server_addr;
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    server_addr.sin_port=htons(SERV_PORT);

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
        perror("listen error");
        exit(0);
    }

    //构造pollfd结构体
    struct pollfd fds[1024];
    int max_index=0;
    //init pollfd array
    for(int i=0;i<1024;i++)
    {
        fds[i].fd=-1;
        fds[i].events=POLLIN;
    }
    fds[0].fd=sfd;
    max_index+=1;

    //开始循环监视文件pollfd的动态
    while(1)
    {
        int i=0;
        int pret=poll(fds,max_index+1,-1);
        if(pret==-1)
        {
            perror("poll error");
            exit(0);
        }
        if(fds[0].revents&POLLIN)
        {
            //客户端套接字
            struct sockaddr_in client_addr;
            socklen_t client_len=sizeof(client_addr);

            int afd=accept(sfd,(struct sockaddr *)&client_addr,&client_len);
            if(afd==-1)
            {
                perror("accept error");
                exit(0);
            }

            for(i=0;i<1024;i++)
            {
                if(fds[i].fd==-1)
                {
                    fds[i].fd=afd;
                    break;
                }
            } 

            max_index=max_index<i?i:max_index;
        }

        //处理客户端的读操作
        for(int i=1;i<=max_index;i++)
        {
            int fd=fds[i].fd;
            if(fds[i].fd==-1)
            {
                continue;
            }
            if(fds[i].revents&POLLIN)
            {
                char msgBuf[1024]={0};
                int len=recv(fd,msgBuf,sizeof(msgBuf),0);
                if(len==-1)
                {
                    printf("recv error");
                    exit(0);
                }
                else if(len==0)
                {
                    printf("The client is exit!\n");
                    close(fd);
                    fds[i].fd=-1;
                }
                else
                {
                    printf("recv:%s\n",msgBuf);
                    for(int k=0;k<len;k++)
                    {
                        msgBuf[k]=toupper(msgBuf[k]);
                    }
                    send(fd,msgBuf,strlen(msgBuf)+1,0);
                    printf("send:%s\n",msgBuf);
                }
            }
        }
    }
    close(sfd);
    return 0;
}
