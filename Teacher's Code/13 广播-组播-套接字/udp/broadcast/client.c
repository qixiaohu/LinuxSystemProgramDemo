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

#if 1
    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(9999);
    inet_pton(AF_INET, "127.0.0.1", &serv.sin_addr.s_addr);
#endif
    

    struct sockaddr_in clien;
    clien.sin_family = AF_INET;
    clien.sin_port = htons(8888);
    inet_pton(AF_INET, "0.0.0.0", &clien.sin_addr.s_addr);
    bind(fd, (struct sockaddr*)&clien, sizeof(clien));


    while(1)
    {
        // 接收数据
        char buf[1024];
        socklen_t len  = sizeof(serv);
#if 0
        recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr*)&serv, &len);
#else
        recvfrom(fd, buf, sizeof(buf), 0, NULL, 0);
#endif
        printf(" recv buf = %s\n", buf);
    }
    return 0;
}
