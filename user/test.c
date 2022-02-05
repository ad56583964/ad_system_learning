#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

#include "kernel/fs.h"

#include "ad_tools.h"

#define INUM_EMPTY 2
#define PRINT_ERROR 2


int
main(int argc, char *argv[]){//指针数组？？

    mkdir("a");
    mkdir("a/b");
    open("a/t",O_CREATE);
    mkdir("a/b/c");

    exit(0);
}
