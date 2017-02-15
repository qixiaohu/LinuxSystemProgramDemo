#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd = open("temo11.txt", O_RDWR | O_CREAT, 0777);
    if(fd == -1)
    {
        perror("open");
        exit(1);
    }
    unlink("temo11.txt");
    write(fd, "hello, world!", 14);

    lseek(fd, 0, SEEK_SET);
    char buf[24] = {0};
    int len = read(fd, buf, sizeof(buf));
    write(STDOUT_FILENO, buf, len);
    printf("buf = %s\n", buf);
    
    for(int i=0; i<1000000; ++i)
    {
    }
    close(fd);
    return 0;
}
