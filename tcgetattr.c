#include <stdio.h>
#include <termio.h>
#include <unistd.h>
#include <errno.h>

int main(void)
{
    //term用于存储获得的终端参数信息
    struct termios term;
    int err;
    //获得标准输入的终端参数，将获得的信息保存在term变量中
    if(tcgetattr(STDIN_FILENO,&term)==-1)
    {
        perror("Cannot get standard input description");
        return 1;
    }
    //修改获得的终端信息的结束控制字符
    term.c_cc[VEOF]=(cc_t)0x07;
    //使用tcsetattr函数修改后的终端参数设置到标准输入中
    //err用于保存函数调用后的结果
    err=tcsetattr(STDIN_FILENO,TCSAFLUSH,&term);
    //如果err为-1或是出现EINTR错误（函数执行被信号中断）
    //给出相关出错信息
    if(err==-1&&err==EINTR)
    {
        perror("Failed to change EOF character");
        return 1;
    }
    return 0; 
}
