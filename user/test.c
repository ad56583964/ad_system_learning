#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

#include "kernel/fs.h"

#include "ad_tools.h"

#define INUM_EMPTY 2
#define PRINT_ERROR 2

void showString(const char* str)
{
    printf("Str:%s\n",str);
}

int
main(int argc, const char *argv[]){//指针数组？？

    // char*
    char* child_argv[16]={0};

    child_argv[0] = (char*)malloc(16);//dynamic memory
    child_argv[1] = (char*)malloc(16);//new when use

    strcpy(child_argv[0],argv[1]);
    strcpy(child_argv[1],argv[2]);

    showString(argv[3]);
/* 

test haha ahah

*/
    while(1)
    {
        static int i = 0;
        if(argv[i] == 0)
        {
            printf("###%p\n",argv[i]);
            break;
        }
        printf("%p\n",argv[i]);
        i++;
    }

    showString(child_argv[0]);
    showString(child_argv[1]);

    printf("start: %s",argv[1]);

    // exec();

    exit(0);
}
