#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>

int main(int argc,const char *argv[])
{
    int sfd=socket(AF_INET,SOCK_STREAM,0);
    if(sfd==-1)
    {
        perror("socket error");
        exit(1);
    }

    struct sockaddr_in sock_addr;
    memset(&sock_addr,0,sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port=htons(9999);
    sock_addr.sin_addr.s_addr=htonl(INADDR_ANY);

    int ret= bind(sfd,(struct sockaddr*)&sock_addr,sizeof(sock_addr));
    if(ret==-1)
    {
        perror("bind error");
        exit(-1);
    }

    int lret= listen(sfd,64);
    if(lret==-1)
    {
        perror("listen error");
        exit(-2);
    }

    struct sockaddr_in sock_addr_a;
    socklen_t sock_len=sizeof(sock_addr_a);

    int afd=accept(sfd,(struct sockaddr *)&sock_addr_a,&sock_len);
    if(afd==-1)
    {
        perror("accept error");
        exit(-3);
    }
    char buf1[128];
    printf("client ip:%s,client port:%d\n",inet_ntop(AF_INET,&sock_addr_a.sin_addr,buf1,sizeof(buf1)),ntohs(sock_addr_a.sin_port));
    while(1)
    {  
        char ipbuf[1024]={0};
        if(afd==-1)
        {
            perror("accept error");
            exit(-3);
        }


        int len=read(afd,ipbuf,sizeof(ipbuf));
        if(len<=0)
        {
            break;
        }
        printf("read:%s\n",ipbuf);
        for(int i=0;i<len;++i)
        {
            ipbuf[i]=toupper(ipbuf[i]);
        }
        printf("after:%s\n",ipbuf);
        write(afd,ipbuf,strlen(ipbuf)+1);
        memset(ipbuf,0,sizeof(ipbuf));
    }

    close(sfd);
    close(afd);
}

