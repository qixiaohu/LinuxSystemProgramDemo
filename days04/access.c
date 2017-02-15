#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
    if(argc<2)
    {
        printf("a.out filename\n");
        exit(0);
    }

    int ret=(int)access(argv[1],X_OK);

    if(ret==-1)
    {
        perror("access");
        exit(0);
    }

    printf("You can write the file!\n");

    return 0;
}
