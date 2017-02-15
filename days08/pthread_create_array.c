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
    printf("I am the %d child!\n",(*(int *)arg));
    return NULL;
}

int i=0;

int main(int argc,const char *argv[])
{
    int array[5]={1,2,3,4,5};
    for(i=0;i<sizeof(array)/sizeof(int);i++)
    {
        pthread_t pthid;
        int ret=pthread_create(&pthid,NULL,myfunc,&array[i]);
        if(ret!=0)
        {
            printf("pthread_create error:%s\n",strerror(ret));
            exit(1);
        }
    }
    sleep(1);
    return 0;
}
