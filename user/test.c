#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

enum{
    PIPE_READ,
    PIPE_WRITE
};

void readOut(int read_pipe)
{
    int read_buf;

    int check_read = 1;
    while(1)
    {
        if(check_read == 0)
        {
            printf("Finished\n");
            break;
        }
        check_read = read(read_pipe,&read_buf,sizeof(int));
        printf("Read: %d, Check: %d\n",read_buf,check_read);
    }
}

void pushInNum(int write_pipe)
{
    for(int i = 0; i <= 5; i++)
    {
        write(write_pipe,&i,sizeof(int));
    }
    // sleep(10);
    close(write_pipe);
}


void parent(int write_pipe)
{
    // for(int i = 0; i <= 5; i++)
    // {
    //     write(write_pipe,&i,sizeof(int));
    // }
}

int
main(int argc, char *argv[])
{
    int p[2];

    pipe(p);

    int pid = fork();

    if(pid == 0){
        pushInNum(p[PIPE_WRITE]);
    }
    else{
        readOut(p[PIPE_READ]);
    }
    exit(0);
}

