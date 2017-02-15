#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctype.h>

int main(int argc, const char* argv[])
{
    int fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8888);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int ret = bind(fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(ret == -1)
    {
        perror("bind error");
        exit(1);
    }

    char bufip[128];
    struct sockaddr_in clien;
    socklen_t clien_len = sizeof(clien);
    while(1)
    {
        char buf[1024] = {0};
        int len = recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr*)&clien, &clien_len);
        if(len == -1)
        {
            perror("recvfrom error");
            exit(1);
        }
        printf("client ip: %s, port: %d\n",
               inet_ntop(AF_INET, &clien.sin_addr.s_addr, bufip, sizeof(bufip)),
               ntohs(clien.sin_port));
        printf("read buf = %s\n", buf);

        for(int i=0; i<len; ++i)
        {
            buf[i] = toupper(buf[i]);
        }

        printf("touper: %s\n", buf);
        len = sendto(fd, buf, strlen(buf)+1, 0, (struct sockaddr*)&clien, clien_len);
        if(len == -1)
        {
            perror("sendto error");
            exit(1);
        }
    }
    close(fd);

    return 0;
}
