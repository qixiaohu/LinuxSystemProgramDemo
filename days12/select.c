#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

int main(int argc ,const char * argv[])
{
    //创建用于通讯的套接字
    int sfd=socket(AF_INET,SOCK_STREAM,0);
    if(sfd==-1)
    {
        perror("socket error");
        exit(0);
    }

    //构造服务器端套接字
    struct sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(9999);
    server_addr.sin_addr.s_addr=INADDR_ANY;

    int bret=bind(sfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
    if(bret==-1)
    {
        perror("bind error");
        exit(0);
    }

    int lret=listen(sfd,-1);
    if(lret==-1)
    {
        perror("listen error");
        exit(0);
    }

    //构造客户端套接字
    struct sockaddr_in client_addr;
    socklen_t sock_len=sizeof(client_addr);

    fd_set test,reads;
    FD_ZERO(&reads);
    FD_SET(sfd,&reads);
    int maxfd=sfd;

    while(1)
    {
        test=reads;
        int sret=select(maxfd+1,&test,NULL,NULL,NULL);
        if(sret==-1)
        {
            perror("select error");
            exit(0);
        }

        if(FD_ISSET(sfd,&test))
        {
            int afd=accept(sfd,(struct sockaddr *)&client_addr,&sock_len);
            if(afd==-1)
            {
                perror("accept error");
                exit(0);
            }

            FD_SET(afd,&reads);

            maxfd=maxfd<afd?afd:maxfd;
        }
        
        for(int i=sfd+1;i<=maxfd;i++)
        {
            if(FD_ISSET(i,&test))
            {
                char buf[1024]={0};
                int len=recv(i,buf,sizeof(buf),0);
                if(len==-1)
                {
                    perror("recv error");
                    exit(0);
                }else if(len==0)
                {
                    printf("客户端关闭了链接....\n");
                    FD_CLR(i,&reads);
                    close(i);
                }
                else
                {
                    printf("read buf=%s\n",buf);
                    for(int j=0;j<len;j++)
                    {
                        buf[j]=toupper(buf[j]);
                    }
                    printf("  after buf==%s\n",buf);

                    send(i,buf,strlen(buf)+1,0);

                }
            }
        }
    }
    close(sfd);
    return 0;
}
