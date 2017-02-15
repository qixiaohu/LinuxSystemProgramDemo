#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/epoll.h>
#include <arpa/inet.h>


int main(int argc, const char* argv[])
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1)
    {
        perror("socket error");
        exit(1);
    }

    // 绑定
    struct sockaddr_in serv;
    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8888);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);

    // 端口复用
    int flag = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));

    int ret = bind(fd, (struct sockaddr*)&serv, sizeof(serv));
    if(ret == -1)
    {
        perror("bind error");
        exit(1);
    }

    // 监听
    ret = listen(fd, 20);
    if(ret == -1)
    {
        perror("listen error");
        exit(1);
    }


    // 创建ｅｐｏｌｌ模型的根节点，　ｆｄ
    int epfd = epoll_create(2000);
    if(epfd == -1)
    {
        perror("epoll_create error");
        exit(1);
    }
    // epoll树上挂节点
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = fd;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
    if(ret == -1)
    {
        perror("epoll_ctl error");
        exit(1);
    }

    struct epoll_event reval[2000];
    while(1)
    {
        // epoll检测事件
        ret = epoll_wait(epfd, reval, 2000, -1);
        printf("=============== epoll_wait ==============\n");
        if(ret == -1)
        {
            perror("epoll_wait error");
            exit(1);
        }

        // ret == 发送变化的ｆｄ的个数
        for(int i=0; i<ret; ++i)
        {
            // 判断是否有新的连接请求
            int myfd = reval[i].data.fd;
            if(myfd == fd)
            {
                struct sockaddr_in client;
                socklen_t client_len = sizeof(client);
                int cfd = accept(fd, (struct sockaddr*)&client, &client_len);
                if(cfd == -1)
                {
                    perror("accept error");
                    exit(1);
                }
#if 1
                // 设置ｃｆｄ为非阻塞
                int flag = fcntl(cfd, F_GETFL);
                flag |= O_NONBLOCK;
                fcntl(cfd, F_SETFL, flag);
#endif

                // cfd 挂到ｅｐｏｌｌ树上
#if 0
                ev.events = EPOLLIN;
#else
                ev.events = EPOLLIN | EPOLLET;
#endif
                ev.data.fd = cfd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &ev);
            }
            else
            {
                char buf[5];
                memset(buf, 0, sizeof(buf));
#if 0
                int len = recv(myfd, buf, sizeof(buf), 0);
                if(len == -1)
                {
                    perror("recv error");
                    exit(1);
                }
                else if(len == 0)
                {
                    printf("client 断开了连接。。。\n");
                    // 从ｅｐｏｌｌ树上删除节点
                    epoll_ctl(epfd, EPOLL_CTL_DEL, myfd, NULL);
                    close(myfd);
                }
                else
                {
                    printf("recv buf = %s\n", buf);
                    //
                    // 发回去　－　ｃｌｉｅｎｔ
                    send(myfd, buf, strlen(buf)+1, 0);
                }
#else
                int len = 0;
                while( (len = recv(myfd, buf, sizeof(buf), 0)) > 0 )
                {
                    write(STDOUT_FILENO, buf, len);
                    send(myfd, buf, len, 0);
                }
#endif

            }
        }
    }

    close(fd);

    return 0;
}
