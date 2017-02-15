#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <stddef.h>

int main(int argc, const char* argv[])
{
    // 创建套接字
    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(fd == -1)
    {
        perror("socket error");
        exit(1);
    }

    // 绑定
    struct sockaddr_un local;
    memset(&local, 0, sizeof(local));
    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, "hello");
    int len = offsetof(struct sockaddr_un, sun_path) + strlen(local.sun_path);
    unlink("hello");
    int ret = bind(fd, (struct sockaddr*)&local, len);
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

    struct sockaddr_un clienaddr;
    len = sizeof(clienaddr);
    printf("accept ...\n");
    int conn = accept(fd, (struct sockaddr*)&clienaddr, &len);
    if(conn == -1)
    {
        perror("accept error");
        exit(1);
    }
    while(1)
    {
        char buf[1024] = {0};
        int len = read(conn, buf, sizeof(buf));
        if(len == -1)
        {
            perror("read error");
            exit(1);
        }
        printf("read buf = %s\n", buf);

        write(conn, buf, strlen(buf)+1);
    }

    close(fd);

    return 0;
}
