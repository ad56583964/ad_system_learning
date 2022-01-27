#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int
main(int argc, char *argv[])
{
    // close(0);
    char* s = argv[1];

    printf("argv[1] %s\n",s);

    char *es;

    es = s + strlen(s);

    //1*s + 4*1
    printf("es:%d",es);
    // printf("")
    exit(0);
}
