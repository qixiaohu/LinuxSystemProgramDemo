#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>


// 5个互斥锁
pthread_mutex_t mutex[5];    // 5根筷子

void* dine(void* arg)
{
    int num = (int)arg;     // 第几个哲学家

    int left, right;

    if(num < 4)
    {
        // 前４个哲学家
        right = num;
        left = num+1;
    }
    else if(num == 4)
    {
        // 第五个
        right = 0;
        left = num;
    }

    // 吃饭
    while(1)
    {
        // 对右手筷子加锁
        pthread_mutex_lock(&mutex[right]);
        // 尝试对左手加锁
        if(pthread_mutex_trylock(&mutex[left]) == 0)
        {
            //　吃饭
            printf("%c 正在吃面。。。。。。\n", num+'A');
            pthread_mutex_unlock(&mutex[left]);
        }
        // 右手解锁
        pthread_mutex_unlock(&mutex[right]);
        
        sleep(rand()%5);
    }

    return NULL;
}


int main(int argc, const char* argv[])
{
    pthread_t p[5];

    for(int i=0; i<5; ++i)
    {
        pthread_create(&p[i], NULL, dine,  (void*)i);
    }

    for(int i=0; i<5; ++i)
    {
        pthread_mutex_init(&mutex[i], NULL);
    }


    for(int i=0; i<5; ++i)
    {
        pthread_join(p[i], NULL);
    }

    for(int i=0; i<5; ++i)
    {
        pthread_mutex_destroy(&mutex[i]);
    }

    return 0;
}

