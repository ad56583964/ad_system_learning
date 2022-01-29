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
    static char buf[100]; // the size is 100
    // int fd;

  // Ensure that three file descriptors are open.
    // while((fd = open("console", O_RDWR)) >= 0){
    //     if(fd >= 3){
    //         close(fd);
    //         break;
    //     }
    // }
    // char cache;
    while(getcmd(buf, sizeof(buf)) >= 0)
    {
        if(buf[0] == 'h' && buf[1] == 'o' && buf[2] == ' '){
            buf[strlen(buf)-1] = 0;
        }
        fprintf(2, "buf[n-1]: %d\n",buf[strlen(buf)-1]);
        fprintf(2, "buf: %p\n",buf);
        fprintf(2, "buf+3: %p\n",buf+3);
    }

    // how to break? the sh cannot be broken
    printf("exit test\n");
    while(1);
    exit(0);
}
