#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int
getcmd(char *buf, int nbuf) //sizeof buf
{
    // fprintf(2, "buf[0]: %d\n",buf[0]);
    fprintf(2, "@ "); // output to error?? 
    memset(buf, 0, nbuf); //set?? full 0??
    gets(buf, nbuf);  // gets??

    if(buf[0] == 0) // EOF
        return -1;
    return 0;
}

int
main(int argc, char *argv[])
{
    // static char buf[100]; // the size is 100
    
    printf("%s:\n", argv[1]);

    printf("exit test\n");
    // while(1);
    exit(0);
}
