#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main(int argc,char *argv[])
{
    if(argc<2)
    {
        printf("./a.out filename\n");
        exit(0);
    }

    struct stat st;
    int ret=stat(argv[1],&st);
    if(ret==-1)
    {
        perror("stat");
        exit(0);
    }

    char paras[11]={0};

    switch(st.st_mode&S_IFMT)
    {
    case S_IFLNK:
        paras[0]='l';
        break;
    case S_IFDIR:
        paras[0]='d';
        break;
    case S_IFREG:
        paras[0]='-';
        break;
    case S_IFBLK:
        paras[0]='b';
        break;
    case S_IFCHR:
        paras[0]='c';
        break;
    case S_IFIFO:
        paras[0]='P';
        break;
    case S_IFSOCK:
        paras[0]='s';
        break;
    default:
        paras[0]='?';
        break;
    }

    paras[1]=(st.st_mode&S_IRGRP)?'r':'-';
    paras[2]=(st.st_mode&S_IWUSR)?'w':'-';
    paras[3]=(st.st_mode&S_IXUSR)?'x':'-';

    paras[4]=(st.st_mode&S_IRGRP)?'r':'-';
    paras[5]=(st.st_mode&S_IWGRP)?'w':'-';
    paras[6]=(st.st_mode&S_IXGRP)?'x':'-';

    paras[7]=(st.st_mode&S_IROTH)?'r':'-';
    paras[8]=(st.st_mode&S_IWOTH)?'w':'-';
    paras[9]=(st.st_mode&S_IXOTH)?'x':'-';

    int hardlink=st.st_nlink;
    char *user=getpwuid(st.st_uid)->pw_name;
    char *group=getgrgid(st.st_gid)->gr_name;
    int filesize=(int)st.st_size;
    char * time1=ctime(&st.st_mtime);
    char mtime[512]={0};
    strncpy(mtime,time1,strlen(time1)-1);
    char buf[1024];
    sprintf(buf,"%s %d %s %s %d %s %s",paras,hardlink,user,group,filesize,mtime,argv[1]);

    printf("%s\n",buf);

    return 0;
    
}
