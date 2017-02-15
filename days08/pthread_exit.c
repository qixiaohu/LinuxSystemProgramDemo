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
    printf("I am the child pthread1!\n");
    sleep(5);
    printf("I am the child pthread2!\n");
}

int main(int argc,const char *argv[])
{
    pthread_t pthread;
    int ret=pthread_create(&pthread,NULL,myfunc,NULL);
    if(ret!=0)
    {
        printf("pthread_create error:%s\n",strerror(ret));
        exit(0);
    }
   pthread_detach(pthread);
   printf("父进程已死！\n");
//   pthread_exit(NULL);
}
