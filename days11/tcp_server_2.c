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
    struct sockaddr_in sock_addr_b;
    sock_addr_b.sin_family=AF_INET;
    sock_addr_b.sin_addr.s_addr=htonl(INADDR_ANY);
    sock_addr_b.sin_port=htons(9999);
    int bret=bind(sfd,(struct sockaddr *)&sock_addr_b,sizeof(sock_addr_b));
    if(bret==-1)
    {
        perror("bind error");
        exit(0);
    }
    
    int lret=listen(sfd,128);
    if(lret==-1)
    {
        perror("listen error");
        exit(-2);
    }


    struct sockaddr_in sock_addr_a;
    socklen_t sock_len=sizeof(sock_addr_a);
    int aret=accept(sfd,(struct sockaddr *)&sock_addr_a,&sock_len);
    if(aret==-1)
    {
        printf("accept error");
        exit(-3);
    }
    char abuf[128]={0};
    while(1)
    {
        printf("client IP:%s,client Port:%d\n",inet_ntop(AF_INET,&sock_addr_a.sin_addr.s_addr,abuf,sock_len),ntohs(sock_addr_a.sin_port));
        char buf[1024]={0};
        int len = read(aret,buf,sizeof(buf));
        printf("read:%s\n",buf);
        for(int i=0;i<len;i++)
        {
            buf[i]=toupper(buf[i]);
        }
        write(aret,buf,strlen(buf)+1);
        printf("after:%s\n",buf);
    }


}
