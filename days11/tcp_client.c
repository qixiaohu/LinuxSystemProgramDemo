#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc,const char *argv[])
{
    int cfd=socket(AF_INET,SOCK_STREAM,0);
    if(cfd==-1)
    {
        perror("socket error");
        exit(-1);
    }
    struct sockaddr_in sock_addr;
    sock_addr.sin_family=AF_INET;
    sock_addr.sin_port=htons(9999);
//    sock_addr.sin_addr.s_addr=ntopl(127.0.0.1);
    inet_pton(AF_INET,"127.0.0.1",&sock_addr.sin_addr.s_addr);
    socklen_t sock_len=sizeof(sock_addr);
    int nret=connect(cfd,(struct sockaddr*)&sock_addr,sock_len);
    if(nret==-1)
    {
        perror("connect error");
        exit(-2);
    }
    while(1)
    {
       char buf[1024]={0};
       fgets(buf,sizeof(buf),stdin);
//       printf("%s\n",buf);
       write(cfd,buf,sizeof(buf));  
       int len=read(cfd,buf,strlen(buf)+1);
       if(len==0)
       {
           break;
       }
       printf("%s\n",buf);
       memset(buf,0,sizeof(buf));
    }
}
