#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

void recyle_child(int num)
{
    pid_t wpid = waitpid(0, NULL, WNOHANG);
    printf("=========child pid = %d\n", wpid);
}

int main(int argc, const char* argv[])
{
    // 设置ｓｉｇｃｈｌｄ信号阻塞
    sigset_t blockset, old;
    sigemptyset(&blockset);
    sigaddset(&blockset, SIGCHLD);
    sigprocmask(SIG_BLOCK, &blockset, &old);
    pid_t pid = fork();
    if(pid == -1)
    {
        perror("fork error");
        exit(1);
    }

    if(pid > 0)
    {
        // 注册信号捕捉函数
        struct sigaction act;
        act.sa_flags = 0;
        sigemptyset(&act.sa_mask);
        act.sa_handler = recyle_child;

        sigaction(SIGCHLD, &act, NULL);
        // 解除ｓｉｇｃｈｌｄ信号的阻塞
        // sigprocmask(SIG_UNBLOCK, &blockset, NULL);
        sigprocmask(SIG_SETMASK, &old, NULL);
        while(1)
        {
            printf("parent process\n");
            sleep(1);
        }
    }
    else if(pid  == 0)
    {
        printf("child pid = %d\n", getpid());
    }

    return 0;
}
