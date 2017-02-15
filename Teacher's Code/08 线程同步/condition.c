#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>

typedef struct node
{
    int date;
    struct node* next;
}Node;

// 永远指向链表第一个节点的指针
Node* head = NULL;
pthread_mutex_t mutex;
pthread_cond_t cond;


void* producer(void* arg)
{
    while(1)
    {
        // 创建新节点
        Node* newNode = (Node*)malloc(sizeof(Node));
        // init
        newNode->date = rand() % 1000;

        // 加锁，　保护共享数据
        pthread_mutex_lock(&mutex);
        // 头插法
        newNode->next = head;
        head = newNode;
        printf("+++++ 生产者：%lu, %d\n", pthread_self(), newNode->date);
        pthread_mutex_unlock(&mutex);

        // 通知消费者消费
        pthread_cond_signal(&cond);

        usleep(rand() % 100);
    }
}

void* customer(void* arg)
{
    // 一直消费
    while(1)
    {
        pthread_mutex_lock(&mutex);
        // 判断链表是否为空
        while(head == NULL)
        {
            // 消费者阻塞等待
            pthread_cond_wait(&cond, &mutex);
        }
        // 消费
        Node* del = head;
        // 头指针后移
        head = head->next;
        printf("----- 消费者：%lu, %d\n", pthread_self(), del->date);
        // 释放　内存
        free(del);
        pthread_mutex_unlock(&mutex);

        usleep(rand() % 1000);
    }
}

int main(int argc, const char* argv[])
{
    pthread_t p1, p2;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&p1, NULL, producer, NULL);
    pthread_create(&p1, NULL, producer, NULL);
    pthread_create(&p1, NULL, producer, NULL);
    pthread_create(&p1, NULL, producer, NULL);
    pthread_create(&p1, NULL, producer, NULL);
    pthread_create(&p1, NULL, producer, NULL);
    pthread_create(&p2, NULL, customer, NULL);
    pthread_create(&p2, NULL, customer, NULL);
    pthread_create(&p2, NULL, customer, NULL);
    pthread_create(&p2, NULL, customer, NULL);
    pthread_create(&p2, NULL, customer, NULL);
    pthread_create(&p2, NULL, customer, NULL);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
