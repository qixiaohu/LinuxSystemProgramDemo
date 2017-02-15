#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <poll.h>

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

    // poll结构体
    struct pollfd allfd[1024];
    int max_index = 0;
    // init
    for(int i=0; i<1024; ++i)
    {
        allfd[i].fd = -1;
        allfd[i].events = POLLIN;
    }
    allfd[0].fd = lfd;

    while(1)
    {
        int i = 0;
        int ret = poll(allfd, max_index+1, -1); 
        if(ret == -1)
        {
            perror("poll error");
            exit(1);
        }

        // 判断是否有连接请求
        if(allfd[0].revents & POLLIN)
        {
            clien_len = sizeof(clien_addr);
            // 接受连接请求
            int cfd = accept(lfd, (struct sockaddr*)&clien_addr, &clien_len);
            printf("============\n");

            // cfd添加到ｐｏｌｌ数组
            for(i=0; i<1024; ++i)
            {
                if(allfd[i].fd == -1)
                {
                    allfd[i].fd = cfd;
                    break;
                }
            }
            // 更新最后一个元素的下标
            max_index = max_index < i ? i : max_index;
        }

        // 遍历数组
        for(i=1; i<=max_index; ++i)
        {
            int fd = allfd[i].fd;
            if(fd == -1)
            {
                continue;
            }
            if(allfd[i].revents & POLLIN)
            {
                // 接受数据
                char buf[1024] = {0};
                int len = recv(fd, buf, sizeof(buf), 0);
                if(len == -1)
                {
                    perror("recv error");
                    exit(1);
                }
                else if(len == 0)
                {
                    allfd[i].fd = -1;
                    close(fd);
                    printf("客户端已经主动断开连接。。。\n");
                }
                else
                {
                    printf("recv buf = %s\n", buf);
                    for(int k=0; k<len; ++k)
                    {
                        buf[k] = toupper(buf[k]);
                    }
                    printf("buf toupper: %s\n", buf);
                    send(fd, buf, strlen(buf)+1, 0);
                }

            }

        }
    }

    close(lfd);
    return 0;
}
