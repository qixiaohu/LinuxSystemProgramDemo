#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>

void * myreturn()
{
    return NULL;
}

void* myfunc(void* arg)
{
    for(int i=0; i<9; ++i)
    {
        if(i == 4)
        {
           // pthread_exit(NULL);
           // 杀死所以的线程
           // exit(1);
           // return NULL;
           myreturn();
        }
        printf("child pthread , i = %d, pthreadid = %lu\n", i, pthread_self());
    }
    return NULL;
}

int main(int argc, const char* argv[])
{
    pthread_t pthid;
    int ret = pthread_create(&pthid, NULL, myfunc, NULL);
    if(ret != 0)
    {
        // 打印错误信息
        printf("pthread_create error: %s", strerror(ret));
    }
    pthread_detach(pthid);

    pthread_exit(NULL); // 主线程退出

        // 阻塞函数
    // pthread_join(pthid, NULL);

    
    return 0;
}
