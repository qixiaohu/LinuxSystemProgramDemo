#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


int main(int argc, const char* argv[])
{
    char *name = ttyname(0);
    printf("file name = %s\n", name);

    name = ttyname(1);
    printf("file name = %s\n", name);
    
    name = ttyname(2);
    printf("file name = %s\n", name);

    return 0;
}
