#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>

int number = 0;
// 创建读写锁
pthread_rwlock_t lock;

void* write_func(void* arg)
{
    while(1)
    {
        // 加写锁
        pthread_rwlock_wrlock(&lock);
        number ++;
        usleep(10);
        printf("++++++ write, thread id = %lu, number = %d\n", pthread_self(), number);
        pthread_rwlock_unlock(&lock);
        usleep(1000);
    }

    return NULL;
}

void* read_func(void* arg)
{
    while(1)
    {
        // 加读锁
        pthread_rwlock_rdlock(&lock);
        printf("------ read, thread id = %lu, number = %d\n", pthread_self(), number);
        pthread_rwlock_unlock(&lock);
        usleep(1000);
    }
    return NULL;
}

int main(int argc, const char* argv[])
{
    pthread_t thid[8];

    // init rwlock
    pthread_rwlock_init(&lock, NULL);

    for(int i=0; i<3; ++i)
    {
        pthread_create(&thid[i], NULL, write_func, NULL);
    }

    for(int i=3; i<8; ++i)
    {
        pthread_create(&thid[i], NULL, read_func, NULL);
    }

    for(int i=0; i<8; ++i)
    {
        pthread_join(thid[i], NULL);
    }

    // 销毁
    pthread_rwlock_destroy(&lock);
    return 0;
}
