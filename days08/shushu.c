#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

int count=0;

void *myfunc(void *arg)
{
    for(int i=0;i<5000;i++)
    {
        count++;
        printf("==%d==\n",count);
        usleep(40);
    }
    return NULL;
}

int main(int argc, const char *argv[])
{
    for(int i=0;i<3;i++)
    {
        pthread_t pthread;
        int ret=pthread_create(&pthread,NULL,myfunc,NULL);
        if(ret!=0)
        {
            printf("pthread_create error:%s\n",strerror(ret));
            exit(0);
        }

    }
    sleep(10);
}
