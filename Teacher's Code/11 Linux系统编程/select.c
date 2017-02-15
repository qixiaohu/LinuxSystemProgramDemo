#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <sys/select.h>

#define SERV_PORT 8989

int main(int argc, const char* argv[])
{
    int lfd, cfd;
    struct sockaddr_in serv_addr, clien_addr;
    int serv_len, clien_len;

    // 创建套接字
    lfd = socket(AF_INET, SOCK_STREAM, 0);
    // 初始化服务器 sockaddr_in 
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;                   // 地址族 
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);    // 监听本机所有的IP
    serv_addr.sin_port = htons(SERV_PORT);            // 设置端口 
    serv_len = sizeof(serv_addr);
    // 绑定IP和端口
    bind(lfd, (struct sockaddr*)&serv_addr, serv_len);

    // 设置同时监听的最大个数
    listen(lfd, 36);
    printf("Start accept ......\n");

    int maxfd = lfd;
    fd_set reads, test1;

    // init fd_set
    FD_ZERO(&reads);
    FD_SET(lfd, &reads);

    while(1)
    {
       // d调用ｓｅｌｅｃｔ
        test1 = reads;
        int ret = select(maxfd+1, &test1, NULL, NULL, NULL); 
        if(ret == -1)
        {
            perror("select error");
            exit(1);
        }

        // 判断是否有新的连接到来
        if(FD_ISSET(lfd, &test1))
        {
            clien_len = sizeof(clien_addr);
            cfd = accept(lfd, (struct sockaddr*)&clien_addr, &clien_len); 
            if(cfd == -1)
            {
                perror("accept error");
                exit(1);
            }

            // cfd放到检测读的集合中
            FD_SET(cfd, &reads);
            // 更新最大的文件描述符
            maxfd = maxfd < cfd ? cfd : maxfd;
        }

        // 检测客户端是否有数据到达
        for(int i = lfd+1; i<=maxfd; ++i)
        {
            // 判断文件描述符是否在读集合中
            if(FD_ISSET(i, &test1))
            {
                char buf[1024] = {0};
                int len = recv(i,  buf, sizeof(buf), 0);
                if(len == -1)
                {
                    perror("recv error");
                    exit(1);
                }
                // == 0 客户端主动断开了连接
                else if(len == 0)
                {
                    printf("客户端关闭了连接。。。\n");
                    // 从检测读的集合中删除该文件描述符
                    FD_CLR(i, &reads);
                    close(i);
                }
                else
                {
                    printf("read buf = %s\n",  buf);
                    for(int j=0; j<len; ++j)
                    {
                        buf[j] = toupper(buf[j]);
                    }
                    printf(" after buf == %s\n",  buf);
                    // 发送数据给客户端
                    send(i, buf, strlen(buf)+1, 0);
                }
            }
        }
    }

    close(lfd);
    return 0;
}
