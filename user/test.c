#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

enum{
    PIPE_READ_Id,
    PIPE_WRITE_Id
};

void childReadOut(int p[])
{
    int read_buf;
    int check_read = 1;

    close(p[PIPE_WRITE_Id]);
    while(1)
    {
        if(check_read == 0)
        {
            printf("Finished\n");
            break;
        }
        check_read = read(p[PIPE_READ_Id],&read_buf,sizeof(int));
        printf("Read: %d, Check: %d\n",read_buf,check_read);
    }
}

void parentPushInNum(int p[])
{
    close(p[PIPE_READ_Id]); //child no use
    for(int i = 0; i <= 5; i++)
    {
        write(p[PIPE_WRITE_Id],&i,sizeof(int));
    }
    // sleep(10);
    close(p[PIPE_WRITE_Id]); //release PIPE
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
        parentPushInNum(p);
    }
    else{
        childReadOut(p);
    }
    exit(0);
}

