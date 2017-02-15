#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

// 自定义函数
void myfunc(int num)
{
    printf("catch you signal: %d\n", num);
}

int main(int argc, const char* argv[])
{
    // 注册信号捕捉函数
    signal(SIGINT, myfunc);

    while(1)
    {
        printf("hello\n");
        sleep(1);
    }
    return 0;
}
