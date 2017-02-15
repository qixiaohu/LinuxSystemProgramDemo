#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include <poll.h>

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
    server_addr.sin_port=htons(8888);

    int bret=bind(sfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
    if(bret==-1)
    {
        perror("bind error");
        exit(-2);
    }
    int lret=listen(sfd,64);
    if(lret==-1)
    {
        perror("listen error");
        exit(-3);
    }

    //构造一个pollfd类型的结构体数组
    struct pollfd allfd[1024];
    int max_index=0;

    //inin the array
    for(int i=0;i<1024;i++)
    {
        allfd[i].fd=-1;
        allfd[i].events=POLLIN;
    }

    allfd[0].fd=sfd;

    while(1)
    {
        int i=0;
        int pret=poll(allfd,max_index+1,-1);
        if(pret==-1)
        {
            perror("poll error");
            exit(-4);
        }

            //构造客户端的套接字
            struct sockaddr_in client_addr;
            client_addr.sin_family=AF_INET;

        //判断是否有新的客户端的链接
        if(allfd[0].revents&POLLIN)
        {
            socklen_t client_len=sizeof(client_addr);
            int afd=accept(sfd,(struct sockaddr *)&client_addr,&client_len);
            printf("=================\n");
            if(afd==-1)
            {
                perror("accept error");
                exit(-5);
            }

            for(i=0;i<1024;i++)
            {
                if(allfd[i].fd==-1)
                {
                    allfd[i].fd=afd;
                    break;
                }
            }

            max_index=max_index<i?i:max_index;
        }

        //处理读操作
        for(int i=1;i<=max_index;i++)
        {
            int fd=allfd[i].fd;
            if(fd==-1)
            {
                continue;
            }
            if(allfd[i].revents&POLLIN)
            {
                char  msgBuf[1024]={0};
                int len=recv(fd,msgBuf,sizeof(msgBuf),0);
                if(len==-1)
                {
                    perror("recv error");
                    exit(0);
                }
                else if(len==0)
                {
                    printf("The client is exit!\n");
                    allfd[i].fd=-1;
                    close(fd);
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
