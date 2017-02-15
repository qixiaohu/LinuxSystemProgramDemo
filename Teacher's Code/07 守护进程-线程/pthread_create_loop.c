#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>

void* myfunc(void* arg)
{
#if 0
    printf("child pthread , i = %d\n", *(int *)arg);
#endif
    printf("child pthread , i = %d\n", (int)arg);
    return NULL;
}

int main(int argc, const char* argv[])
{
    pthread_t pthid[5];
    for(int i=0; i<5; ++i)
    {
#if 0
        int ret = pthread_create(&pthid[i], NULL, myfunc, (void*)&i);
#endif
        int ret = pthread_create(&pthid[i], NULL, myfunc, (void*)i);
        if(ret != 0)
        {
            // 打印错误信息
            printf("pthread_create error: %s", strerror(ret));
        }
    }

    sleep(1);
    return 0;
}
