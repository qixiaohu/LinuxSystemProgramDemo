#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, const char* argv[])
{
    int fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8888);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr.s_addr);


    while(1)
    {
        char buf[1024] = {0};
        
        fgets(buf, sizeof(buf), stdin);
        int ret = sendto(fd, buf, strlen(buf)+1, 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
        if(ret == -1)
        {
            perror("sendto error");
            exit(1);
        }
        

        int servlen = sizeof(servlen);
        ret = recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr*)&serv_addr, &servlen);
        if(ret == -1)
        {
            perror("recvfrom error");
            exit(1);
        }
        printf("recv buf = %s\n", buf);
    }
    return 0;
}
