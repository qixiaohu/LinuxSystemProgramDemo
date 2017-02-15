#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>


void myfucn(int num)
{
    static int i = 0;
    printf("hello, world, %d......\n", ++i);
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

    // 注册信号捕捉函数
    struct sigaction act;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    act.sa_handler = myfucn;
    sigaction(SIGALRM, &act, NULL);

    //函数调用
    setitimer(ITIMER_REAL, &val, NULL);
    
    while(1);

    return 0;
}
