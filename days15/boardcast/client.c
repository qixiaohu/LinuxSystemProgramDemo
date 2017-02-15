#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <error.h>
#include <string.h>
#include <sys/socket.h>

int main(int argc,const char *argv[])
{
    int sfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sfd==-1)
    {
        perror("socket error");
        exit(0);
    }

    //服务器端套接字
    struct sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(9999);
    inet_pton(AF_INET,"127.0.0.255",&server_addr.sin_addr.s_addr);

    //客户端套接字
    struct sockaddr_in client_addr;
    memset(&client_addr,0,sizeof(client_addr));
    client_addr.sin_family=AF_INET;
    client_addr.sin_port=htons(8888);
    inet_pton(AF_INET,"0.0.0.0",&client_addr.sin_addr.s_addr);
    bind(sfd,(struct sockaddr *)&client_addr,sizeof(client_addr));


    while(1)
    {
        char buf[1024]={0};
        recvfrom(sfd,buf,sizeof(buf),0,NULL,0);
        printf("%s\n",buf);
    }

    close(sfd);
    return 0;
}
