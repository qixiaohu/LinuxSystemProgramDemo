#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

int count;

void *myfunc(void *arg)
{
    printf("I am the %d child,",*(int *)arg);
    printf("seifID:%ld\n",pthread_self());
    return NULL;
}

int main(int argc,const char *argv[])
{
    pthread_t pthread[3]={0};
    int array[3]={0,1,2};

    for(int i=0;i<sizeof(array)/sizeof(int);i++) 
    {
        int ret=pthread_create(&pthread[i],NULL,myfunc,&array[i]);
    }

    sleep(2);

}
