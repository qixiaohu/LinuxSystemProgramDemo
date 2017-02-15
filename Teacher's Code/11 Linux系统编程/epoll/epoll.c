#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <errno.h>
#include <ctype.h>

#define MAXLINE 8192
#define SERV_PORT 8000
#define OPEN_MAX 1000

int main(int argc, char *argv[])
{
    // 记录是第几个连接上来的客户端
    int num = 0;
    
    // 创建监听的套接字
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);

    // 端口复用
    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    listen(listenfd, 20);

    //创建epoll模型, efd指向红黑树根节点
    int efd = epoll_create(OPEN_MAX);               
    if(efd == -1)
    {
        perror("epoll_create error");
        exit(1);
    }

    // tep: epoll_ctl参数  
    struct epoll_event tep;
    //指定lfd的监听时间为"读"
    tep.events = EPOLLIN; 
    tep.data.fd = listenfd;           
    //将lfd及对应的结构体设置到树上,efd可找到该树
    int res = epoll_ctl(efd, EPOLL_CTL_ADD, listenfd, &tep);    
    if(res == -1)
    {
        perror("epoll_ctl error");
        exit(1);
    }

    socklen_t clilen;
    struct sockaddr_in cliaddr;      
    // ep[] : epoll_wait参数
    struct epoll_event ep[OPEN_MAX]; 
    char buf[MAXLINE], str[INET_ADDRSTRLEN];

    while(1) 
    {
        /*epoll为server阻塞监听事件, ep为struct epoll_event类型数组, OPEN_MAX为数组容量, -1表永久阻塞*/
        int nready = epoll_wait(efd, ep, OPEN_MAX, -1); 
        if(nready == -1)
        {
            perror("epoll_wait error");
            exit(1);
        }

        for (int i = 0; i < nready; i++) 
        {
        		//如果不是"读"事件, 继续循环
            if (!(ep[i].events & EPOLLIN))
            {
            		continue;
          	}		     

            //判断满足事件的fd是不是lfd   
            if (ep[i].data.fd == listenfd) 
            {             
                clilen = sizeof(cliaddr);
                // 接受连接请求
                int connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);

                printf("received from %s at PORT %d\n", 
                        inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), 
                        ntohs(cliaddr.sin_port));
                printf("cfd %d---client %d\n", connfd, ++num);

                tep.events = EPOLLIN; 
                tep.data.fd = connfd;
                res = epoll_ctl(efd, EPOLL_CTL_ADD, connfd, &tep);
                if(res == -1)
                {
                    perror("epoll_ctl error");
                    exit(1);
                }

            } 
            // 不是监听的文件描述符
            else 
            {             
                int sockfd = ep[i].data.fd;
                int n = read(sockfd, buf, MAXLINE);

                //读到0,说明客户端关闭链接
                if (n == 0) 
               	{             
                    //将该文件描述符从红黑树摘除          
                    res = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);  
                    if(res == -1)
                    {
                        perror("epoll_ctl error");
                        exit(1);
                    }
                    //关闭与该客户端的链接
                    close(sockfd);  
                    printf("client[%d] closed connection\n", sockfd);

                } 
               	//出错
                else if (n < 0) 
                {                 
                    perror("read n < 0 error: ");
                    res = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);
                    close(sockfd);
                }
                // 实际读到了字节数
                else 
                {                            
                    for (int j = 0; j < n; j++)
                    {
                        buf[j] = toupper(buf[j]);   //转大写,写回给客户端
                    }

                    write(STDOUT_FILENO, buf, n);
                    write(sockfd, buf, n);
                }
            }
        }
    }
    close(listenfd);
    close(efd);

    return 0;
}

