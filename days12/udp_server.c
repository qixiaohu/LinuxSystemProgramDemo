#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <string.h>

int main(int agrc,const char *argv[])
{
    int ret1=socket(AF_INET,SOCK_DGRAM,0);
    if(ret1==-1)
    {
        perror("socket error");
        exit(-1);
    }

    char rbuf[1024]={0};
    //服务器端套接字
    struct sockaddr_in src_addr;
    src_addr.sin_family=AF_INET;
    src_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    src_addr.sin_port=htons(9999);
    bind(ret1,(struct sockaddr *)&src_addr,sizeof(src_addr));

    //客户端套接字
    struct sockaddr_in client_addr;
    socklen_t sock_len=sizeof(client_addr);
    while(1)
    {
        int rlen=recvfrom(ret1,rbuf,sizeof(rbuf),0,(struct sockaddr *)&client_addr,&sock_len);
        printf("receive:%s\n",rbuf);
        for(int i=0;i<rlen;i++)
        {
            rbuf[i]=toupper(rbuf[i]);
        }
        printf("after:%s\n",rbuf);
        //        inet_pton(AF_INET,(struct sockaddr *)&src_addr.sin_addr.s_addr,buf);
        int slen=sendto(ret1,rbuf,strlen(rbuf)+1,0,(struct sockaddr *)&client_addr,sizeof(src_addr));


    }





}
