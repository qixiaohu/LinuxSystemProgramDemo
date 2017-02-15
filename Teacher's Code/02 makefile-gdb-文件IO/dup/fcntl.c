#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

int main()
{
	int fd = open("mytemp", O_RDWR | O_CREAT, 0664);
	if(fd == -1)
	{
		perror("open");
		exit(1);
	}

#if 0
	// == dup
//	int fd1 = fcntl(fd, F_DUPFD, 0);
#else
	// == dup2
	int fd1 = open("mytemp1", O_RDWR | O_CREAT, 0664);
	if(fd1 == -1)
	{
		perror("open");
		exit(1);
	}

	fcntl(fd, F_DUPFD, fd1);
	printf("fd1 = %d", fd1);
#endif	
	char* p = "hello, world!";
	write(fd1, p, strlen(p));
	close(fd1);
	close(fd);

	return 0;
}
