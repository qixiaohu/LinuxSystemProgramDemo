#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/time.h>

int my_func(int num)
{
    printf("捕获%d\n",num);
}


int main(int argc, const char* argv[])
{
    struct itimerval val;
    // init
    // 第一次出发定时器的时间
    val.it_value.tv_sec = 2;
    val.it_value.tv_usec = 0;

    // 定时器被触发一次之后，　再次多次触发定时器的时间
    // 设置定时周期
    val.it_interval.tv_usec = 0;
    val.it_interval.tv_sec = 1;

    //函数调用
    setitimer(ITIMER_REAL, &val, NULL);
    
    while(1)
    {
       signal(SIGALRM,my_func);
    }
    return 0;
}
