#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

// 进程执行过程中，　阻塞某几个信号
int main(int argc, const char* argv[])
{
    // 自定义一个信号集变量
    sigset_t myset;
    // 清空自定义信号集
    sigemptyset(&myset);
    // 添加要阻塞的信号
    sigaddset(&myset, SIGINT);  // ctrl+c
    sigaddset(&myset, SIGQUIT);  // ctrl+/
    sigaddset(&myset, SIGKILL);  // kill -9

    //　设置ｐｃｂ中的阻塞信号集
    sigprocmask(SIG_BLOCK, &myset, NULL);

    // 自定义信号集　－　未决信号集的状态
    sigset_t pendset;

    while(1)
    {
        // 每秒读一次
        sigpending(&pendset);
        // 遍历信号集中的信号
        for( int i=1; i<32; ++i )
        {
            if(sigismember(&pendset, i))
            {
                printf("1");
            }
            else
            {
                printf("0");
            }
        }
        printf("\n");
        sleep(1);
    }
    return 0;
}
