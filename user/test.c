#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int
main(int argc, char *argv[])
{
    // close(0);
    int fd;
    fd = open("console",O_RDWR);
    close(1);
    printf("fd: %d",fd);
    fprintf(fd,"test output\n");
    fprintf(fd,"fffd: %d\n",fd);
    exit(0);
}
