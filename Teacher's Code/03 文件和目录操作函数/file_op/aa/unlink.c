#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, const char* argv[])
{
    int fd = open("abcdefg", O_RDWR | O_CREAT, 0664);
    if(fd == -1)
    {
        perror("open error");
        exit(1);
    }

    // 调用unlink删除该文件
    unlink("abcdefg");
    
    char* p = "让编程改变世界。。。。。。";
    write(fd, p, strlen(p));
    lseek(fd, 0, SEEK_SET);

    // 读文件
    char buf[1024];
    int len = read(fd, buf, sizeof(buf));
    buf[len] = 0;
    printf("buf = %s\n", buf);

    close(fd);
    return 0;
}
