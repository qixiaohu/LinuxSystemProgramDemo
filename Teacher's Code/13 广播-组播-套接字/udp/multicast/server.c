#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <arpa/inet.h>
#include <net/if.h>


int main(int argc, const char* argv[])
{
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd == -1)
    {
        perror("socket error");
        exit(1);
    }

    // 绑定
    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(9999);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    int ret = bind(fd, (struct sockaddr*)&serv, sizeof(serv));
    if(ret == -1)
    {
        perror("bind error");
        exit(1);
    }

    // ｉｎｉｔ　ｃｌｉｅｎｔ
    struct sockaddr_in client;
    bzero(&client, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(8888);
    inet_pton(AF_INET, "239.0.0.10", &client.sin_addr.s_addr);

    // 开启组播权限
    struct ip_mreqn group;
    inet_pton(AF_INET, "239.0.0.10", &group.imr_multiaddr);
    inet_pton(AF_INET, "0.0.0.0", &group.imr_address);
    group.imr_ifindex = if_nametoindex("ens33");
    setsockopt(fd, IPPROTO_IP, IP_MULTICAST_IF, &group, sizeof(group));

    while(1)
    {
        static int i = 0;
        char buf[1204];
        sprintf(buf, "buf = %s, %d\n", "hello, world", i++);
        sendto(fd, buf, strlen(buf)+1, 0, (struct sockaddr*)&client, sizeof(client));
        printf("send buf: %s\n", buf);
        sleep(1);
    }

    close(fd);
    return 0;
}
