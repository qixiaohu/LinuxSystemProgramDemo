#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>


typedef struct people
{
    int id;
    char name[24];
}People;


People p;
void* myfunc(void* arg)
{
    p.id = 100;
    strcpy(p.name, "jack");
    for(int i=0; i<5; ++i)
    {
        printf("child thread id: %lu, i = %d\n", pthread_self(), i);
    }
    // return &p;
    pthread_exit(&p);
}

int main(int argc, const char* argv[])
{
    pthread_t pthid;

    people pp;
    // 创建子线程
    pthread_create(&pthid, NULL, myfunc, NULL);

    // 阻塞回收子线程
    void* ret = NULL;
    pthread_join(pthid, &ret);

    People* p = (People*)ret;
    printf("people id = %d, name = %s\n", p->id, p->name);

    return 0;
}
