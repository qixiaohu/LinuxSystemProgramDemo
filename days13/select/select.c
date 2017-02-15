#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <strings.h>
#include <sys/select.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

#define SERV_PORT 9999

int main(int argc,const char *argv[])
{
    int afd;
    int sfd=socket(AF_INET,SOCK_STREAM,0);
    if(sfd==-1)
    {
        perror("socket error");
        exit(0);
    }
    //服务器端的套接字
    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    server_addr.sin_port=htons(SERV_PORT);
    int bret=bind(sfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
    if(bret==-1)
    {
        perror("bind error");
        exit(0);
    }
    int lret=listen(sfd,64);
    if(lret==-1)
    {
        perror("listen error");
        exit(0);
    }

    int maxfd=sfd;
    fd_set test,reads;
    FD_ZERO(&reads);
    FD_SET(sfd,&reads);

    while(1)
    {
        test=reads;
        //使用select函数监控有IO变化的文件描述符
        //通过select函数，test函数中，有IO变化的文件描述符位会被置1
        //没有变化的会被清0，这也是FD_ISSET函数工作的前提
        //select函数返回改变的文件描述符的个数
        int sret=select(maxfd+1,&test,NULL,NULL,NULL);
        if(sret==-1)
        {
            perror("select error");
            exit(0);
        }

        struct sockaddr_in client_addr;
        client_addr.sin_family=AF_INET;
        socklen_t addr_len=sizeof(client_addr);
        if(FD_ISSET(sfd,&test))
        {
            //客户端服务器套接字
            afd=accept(sfd,(struct sockaddr *)&client_addr,&addr_len);
            if(afd==-1)
            {
                perror("accept error");
                exit(0);
            }
            FD_SET(afd,&reads);

            maxfd=maxfd<afd?afd:maxfd;
        }

        //文件描述表有IO变化，select阻塞被打断，且不是监听文件描述符在变化
        //那么可定是其他的“读”的文件描述符发生了变化，但是select函数只检测变化
        //不能确定是具体的哪个发生了变化，所一，我们遍历文件描述符表
        for(int i=sfd+1;i<=maxfd;++i)
        {
            if(FD_ISSET(i,&test))
            {
                char msgBuf[1024]={0};
                int len=recv(i,msgBuf,sizeof(msgBuf),0);
                if(len==-1)
                {
                    perror("recv error");
                    exit(0);
                }
                //如果客户端没有关闭，则服务端一直阻塞等待客户端的输入
                //如果客户端所有的“写设备”全部关闭，则服务端则会读“0”
                else if(len==0)
                {
                    printf("The client is closed!\n");
                    FD_CLR(i,&reads);
                    close(i);
                }
                else
                {
                    printf("recv:%s\n",msgBuf);
                    for(int j=0;j<len;j++)
                    {
                        msgBuf[j]=toupper(msgBuf[j]);
                    }
                    printf("send:%s\n",msgBuf);
                    send(i,msgBuf,strlen(msgBuf)+1,0);
                }
            }
        }
    }
    close(sfd);
    return 0;
}
