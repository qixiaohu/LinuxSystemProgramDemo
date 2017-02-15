#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <string.h>

int main(int argc,const char *argv[])
{
    int sfd=socket(AF_INET,SOCK_STREAM,0);
    if(sfd==-1)
    {
        perror("socket error");
        exit(-1);
    }

    struct sockaddr_in sock_addr_s;
    sock_addr_s.sin_family=AF_INET;
    sock_addr_s.sin_addr.s_addr=htonl(INADDR_ANY);
    sock_addr_s.sin_port=htons(9999);
    int bret=bind(sfd,(struct sockaddr *)&sock_addr_s,sizeof(sock_addr_s));
    if(bret==-1)
    {
        perror("bind error");
        exit(0);
    }

    int lret=listen(sfd,64);
    if(lret==-1)
    {
        perror("listen error");
        exit(-2);
    }

    struct sockaddr_in sock_addr_a;
    socklen_t sock_len;
    int afd;

    while(1)
    {
        char buf[1024]={0};
        afd=accept(sfd,(struct sockaddr *)&sock_addr_a,&sock_len);
        if(afd==-1)
        {
            perror("accept error");
            exit(-3);
        }
        char pbuf[128]={0};
        printf("client ip:%s,client port:%d\n",inet_ntop(AF_INET,&sock_addr_a.sin_addr,pbuf,sizeof(pbuf)),ntohs(sock_addr_a.sin_port));
        int len= read(afd,buf,sizeof(buf));
        printf("read:%s\n",buf);
        for(int i=0;i<len;i++)
        {
            buf[i]=toupper(buf[i]);
        }
        printf("after:%s\n",buf);
        write(afd,buf,strlen(buf)+1);
    }
}


