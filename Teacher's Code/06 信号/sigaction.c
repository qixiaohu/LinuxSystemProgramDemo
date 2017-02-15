#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>


void myfunc(int num)
{
    printf("catch you signal: %d\n", num);
    sleep(5);
    printf("wake up======\n");
}

int main(int argc, const char* argv[])
{
    struct sigaction act;
    // intit
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    // 临时屏蔽ｃｔｒｌ＋
    sigaddset(&act.sa_mask, SIGQUIT);
    act.sa_handler = myfunc;

    // 注册
    sigaction(SIGINT, &act, NULL);

    while(1)
    {

    }

    return 0;
}
