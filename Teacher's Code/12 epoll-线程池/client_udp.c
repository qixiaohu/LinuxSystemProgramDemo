#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <arpa/inet.h>


// udp - client
int main(int argc, const char* argv[])
{
    // 创建套接字　－　通信
    int  fd = socket(AF_INET, SOCK_DGRAM, 0);

    // 初始化服务器的ＩＰ和端口
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9999);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr.s_addr);

    socklen_t servlen = sizeof(servaddr);

    while(1)
    {
        char buf[1024] = {0};
        // 给服务器发数据
        fgets(buf, sizeof(buf), stdin);
        sendto(fd, buf, strlen(buf)+1, 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
        // 接受数据
        int ret = recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr*)&servaddr, &servlen);
        printf("buf = %s\n", buf);
        if(ret == -1)
        {
            perror("recvform error");
            exit(1);
        }
    }
    return 0;
}
