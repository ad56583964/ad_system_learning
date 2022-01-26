#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    // int ch = argv[0];
    int ch_time = atoi(argv[1]);
    // write(1, argv[1], 1);
    // write(1, "\n", 1);
    // sleep(2);
    // fprintf(1,"%d\n",ch);
    sleep(ch_time);
    exit(0);
}
