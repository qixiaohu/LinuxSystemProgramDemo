#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>

int fd;

void myfunc(int num)
{
    time_t timep;
    time(&timep);
    char *buf=asctime(gmtime(&timep));
    write(fd,buf,strlen(buf));
}

int main(int argc,const char *argv[])
{
    pid_t pid =fork();
    if(pid==-1)
    {
        perror("fork error");
        exit(0);
    }
    if(pid>0)
    {
        exit(0);
    }
    else if(pid==0)
    {
        pid_t pid1=setsid();
        fd=open("./time1.txt",O_RDWR|O_CREAT|O_APPEND,0777);
        if(pid1==-1)
        {
            perror("setsid error");
            exit(0);
        }
        //守护进程不需要终端，关闭标准文件描述符
        close(0);
        close(1);
        close(2);
        //改变工作目录
#if 0
        int dir= chdir("/home/itheima/test/days08");
        if(dir==-1)
        {
            perror("chdir error");
            exit(0);
        }
#endif
        //重设掩码
        //umask(0777);
        struct itimerval tval;
        //开始时间
        tval.it_value.tv_sec=1;
        tval.it_value.tv_usec=0;
        //循环周期
        tval.it_interval.tv_sec=3;
        tval.it_interval.tv_usec=0;

        setitimer(ITIMER_REAL,&tval,NULL);

        while(1)
        {
            //捕捉时钟周期结束信号
            struct sigaction act;
            act.sa_flags=0;
            sigemptyset(&act.sa_mask);
            act.sa_handler=myfunc;
            sigaction(SIGALRM,&act,NULL);
        }
    }
    return 0;
}
