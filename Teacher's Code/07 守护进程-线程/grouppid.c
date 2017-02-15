#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>


int main(int argc, char *argv[])
{
	pid_t pid = fork();

	if(pid > 0)
	{
		printf("++++++before: \n");
		printf("parent pid = %d, pgid = %d\n", getpid(), getpgrp());
		printf("child pid = %d, pgid = %d\n", pid, getpgid(pid));
		printf("------after: \n");
		// 孩子提拔为组长
		setpgid(pid, pid);
		printf("child pid = %d, pgid = %d\n", pid, getpgid(pid));
	}
	else if(pid == 0)
	{
		printf("child pid = %d, pgid = %d\n", pid, getpgrp());

	}

	return 0;
}


