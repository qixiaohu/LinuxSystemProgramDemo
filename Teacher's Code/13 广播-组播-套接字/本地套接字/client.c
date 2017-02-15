#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <arpa/inet.h>
#include <stddef.h>
#include <sys/un.h>

int main(int argc, const char* argv[])
{
    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(fd == -1)
    {
        perror("socket error");
        exit(1);
    }

    // 绑定套接字文件
    struct sockaddr_un local;
    memset(&local, 0, sizeof(local));
    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, "world");
    int len = offsetof(struct sockaddr_un, sun_path) + strlen(local.sun_path);
    int ret = bind(fd, (struct sockaddr*)&local, len);
    if(ret == -1)
    {
        perror("bind error");
        exit(1);
    }

    // init server info
    struct sockaddr_un serv;
    serv.sun_family = AF_UNIX;
    strcpy(serv.sun_path, "hello");

    // 连接
    len = offsetof(struct sockaddr_un, sun_path) + strlen(serv.sun_path);
    ret = connect(fd, (struct sockaddr*)&serv, len); 
    if(ret == -1)
    {
        perror("connect error");
        exit(1);
    }

    while(1)
    {
        char buf[64];
        fgets(buf, sizeof(buf), stdin);
        write(fd, buf, strlen(buf)+1);

        read(fd, buf, sizeof(buf));
        printf("read buf = %s\n", buf);
    }
    close(fd);

    return 0;
}
