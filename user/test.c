#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int
main(int argc, char *argv[])
{
    char cache;
    
    while(1)
    {
        static int string_cnt = 1;
        static int check_read = 1;

        check_read = read(0,&cache,1);
        string_cnt++;

        printf("ID:%d C:%c D:%d CHECK:%d\n",string_cnt,cache,check_read);
        //ASCALL 0:

        if (check_read == 0)
        {
            break;
        }
        
    }

    exit(0);
}
