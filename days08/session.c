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

void myfunc(int num)
{
    int fd=open("./time.txt",O_RDWR|O_CREAT,0664);
    if(fd==-1)
    {
        perror("open error");
        exit(0);
    }
    time_t timep;
    time(&timep);
    char *buf=asctime(gmtime(&timep));
    read(fd,buf,strlen(buf));
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
        int dir= chdir("/home/itheima/test/days08");
        if(dir==-1)
        {
            perror("chdir error");
            exit(0);
        }
        //重设掩码
        umask(0777);

        struct itimerval tval;
        //开始时间
        tval.it_value.tv_sec=0;
        tval.it_value.tv_usec=0;
        //循环周期
        tval.it_interval.tv_sec=3;
        tval.it_interval.tv_usec=0;
        
        //捕捉始终周期结束信号
        struct sigaction act;
        act.sa_flags=0;
        sigemptyset(&act.sa_mask);
        act.sa_handler=myfunc;
        sigaction(SIGALRM,&act,NULL);
        setitimer(ITIMER_REAL,&tval,NULL);
    }
    return 0;
}
