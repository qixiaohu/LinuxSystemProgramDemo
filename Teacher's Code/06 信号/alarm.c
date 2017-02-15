#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


int main(int argc, const char* argv[])
{
#if 1
    int ret = alarm(5);
    printf("ret = %d\n", ret);
    sleep(3);
#endif
    int ret  = alarm(1);

    int i = 0;
    while(1)
    {
        printf("%d\n", ++i);
    }
    return 0;
}
