#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>


int foreach_dir(const char *root)  
{
    DIR *dir=opendir(root);
    if(dir==NULL)
    {
        perror("open dir error");
        exit(0);
    }
    int total=0;
    char buf[1024];
    struct dirent * ptr=NULL;
    while((ptr=(dir))!=NULL)
    {
        if(strcmp(ptr->d_name,".")==0||strcmp(ptr->d_name,"..")==0)
        {
            continue;
        }
        if(ptr->d_type==DT_REG)
        {
            printf("%s\n",ptr->d_name);
            total ++;
        }
        if(ptr->d_type==DT_DIR)
        {
            sprintf(buf,"%s/%s",root,ptr->d_name);
            total+=foreach_dir(buf);
        }

    }

    closedir(dir);

    return total;
}

int main(int argc,char *argv[])
{
    if(argc<2)
    {
        printf("a.out filename\n");
        exit(0);
    }
    int num=foreach_dir(argv[1]);
    printf("num:%d\n",num);

    return 0;
}
