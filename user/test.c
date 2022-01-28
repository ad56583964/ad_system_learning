#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int haha()
{
    printf("Do\n");
    return 0;
}

int
main(int argc, char *argv[])
{
    // char cache;
    char buf[100];

    printf("The Size: %d", sizeof(buf));

    exit(0);
}
