#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc,const char *argv[])
{
    int sfd=socket(AF_INET,SOCK_STREAM,0);
    if(sfd==-1)
    {
        perror("socket error");
        exit(-1);
    }

    struct sockaddr_in sock_addr_c;
    sock_addr_c.sin_family=AF_INET;
    inet_pton(AF_INET,"127.0.0.1",&sock_addr_c.sin_addr.s_addr);
    sock_addr_c.sin_port=htons(9999);

    int ret=connect(sfd,(struct sockaddr *)&sock_addr_c,sizeof(sock_addr_c));
    if(ret==-1)
    {
        perror("connect error");
        exit(-1);
    }
    while(1)
    {
        char buf[1024]={0};
        gets(buf);
        //printf("read:%s\n",buf);
        write(sfd,buf,sizeof(buf));
        read(sfd,buf,strlen(buf)+1);
        printf("read:%s\n",buf);
    }
}
