#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
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
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(9999);
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);

    //绑定
    int bret=bind(sfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
    if(bret==-1)
    {
        perror("bind error");
        exit(0);
    }

    //广播的组的套接字
    struct sockaddr_in client_addr;
    client_addr.sin_family=AF_INET;
    client_addr.sin_port=htons(8888);
    inet_pton(AF_INET,"127.0.0.255",&client_addr.sin_addr.s_addr);

    //开启广播权限
    int opt=1;
    setsockopt(sfd,SOL_SOCKET,SO_BROADCAST,&opt,sizeof(opt));

    while(1)
    {
        static int i=0;
        char buf[1024]={0};
        sprintf(buf,"%s,%d!\n","Hello,World",i++);
        sendto(sfd,buf,strlen(buf)+1,0,(struct sockaddr *)&client_addr,sizeof(client_addr));
        printf("%s\n",buf);
        sleep(1);
    }
    close(sfd);
    return 0;

}
