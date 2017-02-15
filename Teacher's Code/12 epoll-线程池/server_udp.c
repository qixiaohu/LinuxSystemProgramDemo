#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <arpa/inet.h>


// udpserver

int main(int argc, const char* argv[])
{
    // 创建套接字　－　通信
    int  fd = socket(AF_INET, SOCK_DGRAM, 0);

    // 绑定
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9999);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(fd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    // 通信
    struct sockaddr_in clienaddr;
    socklen_t clienlen = sizeof(clienaddr);
    while(1)
    {
        // 接受数据
        char buf[1024] = {0};
        int ret = recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr*)&clienaddr, &clienlen);
        if(ret == -1)
        {
            perror("recvform error");
            exit(1);
        }
        char bufip[64];
        printf("client ip: %s, port: %d\n", 
               inet_ntop(AF_INET, &clienaddr.sin_addr.s_addr, bufip, sizeof(bufip)),
               ntohs(clienaddr.sin_port));

        // 给客户端发数据
        sendto(fd, buf, strlen(buf)+1, 0, (struct sockaddr*)&clienaddr, sizeof(clienaddr));

    }
    return 0;
}
