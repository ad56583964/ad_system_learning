#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

#include "kernel/fs.h"

#include "ad_tools.h"

#define INUM_EMPTY 2
#define PRINT_ERROR 2

void showString(const char* str){
    printf("Str:%s\n",str);
}

void pushParams(const char* exec_name, char *child_argv[],const char *parent_argv[]){
    

    int i;
    child_argv[0] = (char*)malloc(16);
    strcpy(child_argv[0],exec_name);
    for(i = 1; parent_argv[i+1] != 0; i++){
        child_argv[i] = (char*)malloc(16);//dynamic memory
        strcpy(child_argv[i],parent_argv[i+1]);
        printf("%p\n",parent_argv[i]);
    }
    child_argv[i+1] = 0;
}

void showArgvs(char* argv[]){
    for(int i = 0; argv[i] != 0; i++){
        printf("argv[%d]:%s\n",i,argv[i]);
    }
}

int
main(int argc, const char *argv[]){//指针数组？？

    // char*
    char* child_argv[16];
    char exec_name[16];
    pushParams(argv[0],child_argv,argv);
    showArgvs(child_argv);


    strcpy(exec_name,argv[0]);
    exec(exec_name,child_argv);

    // exec();

    exit(0);
}
/* 

test haha ahah

sh < xargstest.sh

*/