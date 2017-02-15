#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("./a.out wait_pid\n");
        exit(1);
    }
    union sigval mysigval;
    mysigval.sival_int=500;

    pid_t pid = atoi(argv[1]);

    while (1) {
        sigqueue(pid,SIGINT, mysigval);
        printf("send value = %d\n", mysigval.sival_int);
        sleep(2);
    }

	return 0;
}
