#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>

#define SERV_PORT 9999

int main(int argc,const char *argv[])
{
    int lfd,cfd;
    struct sockaddr_in serv_addr,client_addr;
    socklen_t serv_len,client_len;

    lfd=socket(AF_INET,SOCK_STREAM,0);

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(SERV_PORT);
    serv_len=sizeof(serv_addr);

    bind(lfd,(struct sockaddr *)&serv_addr,serv_len);

    listen(lfd,64);

    printf("Start accept......\n");

    //poll结构体
    struct pollfd allfd[1024];
    int max_index=0;

    //初始化poll结构体数组
    for(int i=0;i<1024;i++)
    {
        allfd[i].fd=-1;
        allfd[i].events=POLLIN;
    }

    //poll结构体数组的第一个元素为负责监听的文件描述符
    allfd[0].fd=lfd;

    while(1)
    {
        int i=0;
        int ret=poll(allfd,max_index+1,-1);
        if(ret==-1)
        {
            perror("poll error");
            exit(0);
        }

        //说明用于监听的文件描述符发生了IO操作
        if(allfd[0].revents&POLLIN)    
        {
            client_len=sizeof(client_addr);
            cfd=accept(lfd,(struct sockaddr *)&client_addr,&client_len);
            printf("=============\n");

            //将获得的客户端的文件描述符添加到poll结构体的fd属性中
            for(i=0;i<1024;i++)
            {
                if(allfd[i].fd==-1)
                {
                    allfd[i].fd=cfd;
                    break;
                }
            }

            max_index=max_index<i?i:max_index;
        }

        for(int i=1;i<=max_index;i++)
        {
            int fd=allfd[i].fd;
            if(fd==-1)
            {
                continue;
            }
            if(allfd[i].revents&POLLIN)
            {
                char buf[1024]={0};
                int len=recv(fd,buf,sizeof(buf),0);
                if(len==-1)
                {
                    perror("recv error");
                    exit(1);
                }
                else if(len==0)
                {
                    allfd[i].fd=-1;
                    close(fd);
                    printf("客户端已经主动断开链接....\n");
                }
                else
                {
                    printf("recv:%s\n",buf);
                    for(int k=0;k<len;k++)
                    {
                        buf[k]=toupper(buf[k]);
                    }
                    send(fd,buf,strlen(buf)+1,0);
                    printf("send:%s\n",buf);
                }
            }
        }
    }

    close(lfd);
    return 0;
}
