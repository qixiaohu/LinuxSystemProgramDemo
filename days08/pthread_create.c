#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void *myfunc(void *arg)
{
    printf("I am the %d child!\n",(int)arg);
    return NULL;
}

int i=0;

int main(int argc,const char *argv[])
{
    for(i=1;i<=5;i++)
    {
        pthread_t pthid;
        int ret=pthread_create(&pthid,NULL,myfunc,(void *)i);
        if(ret!=0)
        {
            printf("pthread_create error:%s\n",strerror(ret));
            exit(1);
        }

    }
    
        sleep(1);

    return 0;
}
