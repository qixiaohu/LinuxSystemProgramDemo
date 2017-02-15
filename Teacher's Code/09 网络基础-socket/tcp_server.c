#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

// server
int main(int argc, const char* argv[])
{
    // 创建监听的套接字
    int lfd = socket(AF_INET, SOCK_STREAM, 0);

    // 绑定
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9999);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // 本地多有的ＩＰ
    // 127.0.0.1
    // inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr.s_addr);
    bind(lfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    // 监听
    listen(lfd, 64);

    // 阻塞等待连接请求，　并接受连接请求
    struct sockaddr_in clien_addr;
    socklen_t clien_len = sizeof(clien_addr);
    int cfd = accept(lfd, (struct sockaddr*)&clien_addr, &clien_len);

    char ipbuf[128];
    printf("client iP: %s, port: %d\n", inet_ntop(AF_INET, &clien_addr.sin_addr.s_addr, ipbuf, sizeof(ipbuf)),
           ntohs(clien_addr.sin_port));

    char buf[1024] = {0};
    while(1)
    {
        // read data
        int len = read(cfd, buf, sizeof(buf));
        printf("read buf = %s\n", buf);
        // 小写转大写
        for(int i=0; i<len; ++i)
        {
            buf[i] = toupper(buf[i]);
        }
        printf("after buf = %s\n", buf);

        // 大写串发给客户端
        write(cfd, buf, strlen(buf)+1);
    }

    close(cfd);
    close(lfd);

    return 0;

}
