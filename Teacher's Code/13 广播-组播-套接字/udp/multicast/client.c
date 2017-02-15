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

    struct sockaddr_in clien;
    clien.sin_family = AF_INET;
    clien.sin_port = htons(8888);
    inet_pton(AF_INET, "0.0.0.0", &clien.sin_addr.s_addr);
    bind(fd, (struct sockaddr*)&clien, sizeof(clien));

    // 加入到组播地址
    struct ip_mreqn group;
    inet_pton(AF_INET, "239.0.0.10", &group.imr_multiaddr);
    inet_pton(AF_INET, "0.0.0.0", &group.imr_address);
    group.imr_ifindex = if_nametoindex("ens33");
    setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &group, sizeof(group)); 


    while(1)
    {
        // 接收数据
        char buf[1024];
        recvfrom(fd, buf, sizeof(buf), 0, NULL, 0);
        printf(" recv buf = %s\n", buf);
    }
    return 0;
}
