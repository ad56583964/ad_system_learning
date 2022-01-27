#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

enum{
    PIPE_READ_Id,
    PIPE_WRITE_Id
};

void endTransport(int write_port)
{
    int ch = -1;
    write(write_port,&ch,sizeof(int));
}

void createPipe(int p[])
{
    while(1){
        int check_pipe = pipe(p);//开启第一个管道
        if(check_pipe == 0){
            // close(0);
            break;
        }
        else{
            printf("WaitRelease\n");
            sleep(4);
            // while(1);
        }
    }
}

void pushInNums(int nums,int p[])
{
    // close(p[PIPE_READ_Id]);
    // fprintf(2,"%d: isParent\n",pid);
    //推送数字
    for(int n=2;n<=nums;n++)
    {
        write(p[PIPE_WRITE_Id],&n,sizeof(int));
    }
    endTransport(p[PIPE_WRITE_Id]);
    // break;
    // printf("Closed\n");
    close(p[PIPE_WRITE_Id]);
    close(p[PIPE_READ_Id]);
}

void pipeline(int frompipe[])
{
    int p[2];
    p[0] = frompipe[0];

    int cache_read;
    int cache_write;

    __JUMP:
        int cn;//除数
        read(p[0],&cn,sizeof(int));//get the first num from the pipe and store it as the divisor

        if(cn == -1){ //end of pipe
            // printf("LastPipeLine\n");
            return;
        }

        // sleep(2);
        // printf("N: %d Pipe: %d\n",cn, p[0]);
        printf("prime %d\n",cn, p[0]);
        cache_read = p[0];//last read pipe
        cache_write = p[1];

        createPipe(p);

        int inpid = fork();
        if(inpid == 0){     
            close(cache_read);
            close(cache_read);
            close(p[1]);
            goto __JUMP;
        }
        while(1)//处理管道来的东西
        {
            int dividend;
            read(cache_read,&dividend,sizeof(int));//获取被除数

            if(dividend == -1)// end if pipe
            {
                endTransport(p[PIPE_WRITE_Id]);
                // printf("Finish\n");
                break;
            }

            if(dividend % cn != 0)//find a prime
            {
                write(p[PIPE_WRITE_Id],&dividend,sizeof(int)); //发到新的管道里
            }
        }
        close(cache_read);
        close(cache_write);
        close(p[PIPE_WRITE_Id]);
        close(p[PIPE_READ_Id]);

    // printf("Closed: %d\n",cache_read);
}

int main(void)
{
    // int forkd = 1;
    int p[2]; //pipe
    // int check_read = 1;

    // int cache_read = 0;
    // int cache_write = 0;
    pipe(p);

    int pid = fork();

    if(pid > 0)//父进程
    {
        pushInNums(35,p);

    }

    if(pid == 0)//子进程
    {
        pipeline(p);
    }
    close(0);
    wait(0);
    exit(0);
}