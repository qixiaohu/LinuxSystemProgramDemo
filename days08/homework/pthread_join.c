#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

int i=0;

void *myfunc1(void *arg)
{
    while(i<5)
    {
        printf("I am the child pthread,myselfID:%ld\n",pthread_self());
        sleep(1);
        i++;
        if(i==3)
        {
            return &i;
        }
#if 0
        if(i==3)
        {
            pthread_exit(NULL);
        }
#endif
    }
}

void *myfunc2(void *arg)
{
    sleep(3);
    pthread_cancel(*(long int *)arg);
}

int main(int argc,const char *argv[])
{
    pthread_t pthread1,pthread2;
    int ret1=pthread_create(&pthread1,NULL,myfunc1,NULL);
    int ret2=pthread_create(&pthread2,NULL,myfunc2,&pthread1);
    if(ret1!=0)
    {
        printf("pthread_create error:%s\n",strerror(ret1));
        exit(1);
    }
    if(ret2!=0)
    {
        printf("pthread_create error:%s\n",strerror(ret2));
        exit(2);
    }

    void *retval;
    pthread_join(pthread1,&retval);
    //printf("捕获线程ID:%ld,退出状态:%d\n",(long int)pthread1,*(int *)retval);
    printf("捕获线程ID:%ld,退出状态:%p\n",(long int)pthread1,retval);
    //printf("捕获线程ID:%ld,退出状态:%p\n",(long int)pthread1,retval);
}
