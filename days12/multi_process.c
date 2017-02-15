#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>

void myfunc(int arg)
{
    pid_t wpid;
    while((wpid=waitpid(0,NULL,WNOHANG))>0) 
    {
        printf("子进程被回收,pid:%d\n！",wpid);
    } 
}

int main(int argc,const char *argv[])
{
    int sfd=socket(AF_INET,SOCK_STREAM,0);
    if(sfd==-1)
    {
        perror("socket error");
        exit(-1);
    }

    //服务器端套接字
    struct sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    server_addr.sin_port=htons(9999);

    //注册父进程捕捉信号
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    /*sigaddset(&act.sa_mask,SIGINT);*/
    /*sigaddset(&act.sa_mask, SIGCHLD);*/
    act.sa_flags=0;
    act.sa_handler=myfunc;
    sigaction(SIGCHLD,&act,NULL);


    //绑定套接字
    int bret=bind(sfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
    if(bret==-1)
    {
        perror("bind error");
        exit(-2);
    }

    //监听套接字，并设置最大同时连接数
    int lret=listen(sfd,128);
    if(lret==-1)
    {
        perror("listen error");
        exit(-3);
    }

    //链接至服务器的客户端的套接字
    struct sockaddr_in client_addr;
    client_addr.sin_family=AF_INET;
    socklen_t client_sock_len=sizeof(client_addr);

    int cfd;
    while(1)
    {
        cfd=accept(sfd,(struct sockaddr *)&client_addr,&client_sock_len);
        if(cfd<0)
        {
            continue;
#if 0
            if( errno==EINTR)
            {
                continue;
            } 
            else
            {
                exit(0);
            }
#endif
        }

        pid_t pid=fork();

        if(pid>0)  
        {
            char buf[128]={0};
            inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,buf,sizeof(buf));
            printf("----Client IP:%s----Client port:%d----\n",buf,ntohs(client_addr.sin_port));
        }

        if(pid==0)
        {
            //关闭用于监听的socket【文件描述符】,子进程不需要进行监听
            close(sfd);
            while(1)
            {
                char msgBuf[1024]={0};
                //通信
                int rlen=read(cfd,msgBuf,sizeof(msgBuf));
                if(rlen==0)
                {
                    printf("Read buf is empty,exit!\n");
                    break;                    
                }
                printf("Recv:%s\n",msgBuf);
                for(int i=0;i<rlen;++i)
                {
                    msgBuf[i]=toupper(msgBuf[i]);
                }
                printf("Trans:%s\n",msgBuf);
                write(cfd,msgBuf,rlen);
            }
            //关闭退出的客户端套接字【文件描述符】
            close(cfd);
            return 0;
        }
        else if(pid >0)
        {
            //关闭父进程所持有的客户端的文件描述符，相应的文件描述符的连接计数-1
            close(cfd);
        }
        else
        {
            perror("accept error");
        }
    }
    return 0;
}
