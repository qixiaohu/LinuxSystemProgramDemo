#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>


// 查找文件个数

int get_file_num(const char* root)
{
    int total = 0;
    DIR *dir = opendir(root);
    if(dir == NULL)
    {
        perror("open dir error");
        exit(1);
    }

    // 循环读目录
    char path[1024];
    struct dirent* ptr = NULL;
    while( (ptr = readdir(dir)) != NULL )
    {
        if(strcmp(".", ptr->d_name) == 0 || strcmp("..", ptr->d_name) == 0)
        {
            continue;
        }
        if(ptr->d_type == DT_DIR)
        {
            // 继续读
            // 递归调用
            sprintf(path, "%s/%s", root, ptr->d_name);
            total += get_file_num(path); 
        }
        if(ptr->d_type == DT_REG)
        {
            total++;
        }
    }
    closedir(dir);

    return total;
}

int main(int argc, const char* argv[])
{
    if(argc < 2)
    {
        printf("./a.out path\n");
        exit(1);
    }
    int total = get_file_num(argv[1]);
    printf("%s has regfile number: %d\n", argv[1], total);
    return 0;
}

