#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

// 全局变量
int number;
int flag;

// ｐａｒｅｎｔ　数数
void parent_num(int num)
{
    printf("parent number: %d\n", number);
    number += 2;   // 为下一次的输出做准备
    sleep(1);
    flag = 1;   // 当前一次数数操作完成

}

// child 数数
void child_num(int num)
{
    printf("child number: %d\n", number);
    number += 2;
    sleep(1);
    flag = 1;
}

int main(int argc, const char* argv[])
{
    // 注册信号捕捉函数
    struct sigaction act1, act2;

    // init parent
    act1.sa_flags = 0;
    sigemptyset(&act1.sa_mask);
    sigaddset(&act1.sa_mask, SIGUSR1);
    act1.sa_handler = parent_num;
    sigaction(SIGUSR1, &act1, NULL);

    
    // init  child
    act2.sa_flags = 0;
    sigemptyset(&act2.sa_mask);
    sigaddset(&act2.sa_mask, SIGUSR2);
    act2.sa_handler = child_num;
    sigaction(SIGUSR2, &act2, NULL);

    pid_t pid = fork();
    if(pid == -1)
    {
        perror("fork error");
        exit(1);
    }

    if(pid > 0)
    {
        // 父进程先数
        number = 1;
        parent_num(0);
        while(1)
        {
            if(flag)
            {
                // 父进程数数完成，　发信号给子进程
                kill(pid, SIGUSR2);
                // 等待下一次数数
                flag = 0;
            }
        }
    }
    else if(pid == 0)
    {
        number = 2;
        while(1)
        {
            if(flag)
            {
                kill(getppid(), SIGUSR1);
                flag = 0;
            }
        }

    }
    return 0;
}
