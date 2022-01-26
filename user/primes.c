#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void pipeline(int frompipe[])
{
    int p[2];
    p[0] = frompipe[0];

    int cache_read;
    int check_read = 1;

    while(check_read == 1)
    {
        int cn;//除数
        check_read = read(p[0],&cn,sizeof(int));//get the first num from the pipe and store it as the divisor

        printf("N: %d\n",cn);

        if(check_read == 0){ //read nothing 
            printf("LastPipeLine\n");
            break; //stop and exit[this is the finial process]
        }

        cache_read = p[0];
        pipe(p); //创建新管道 /这个时候p的值就变了


        while(check_read != 0)//处理管道来的东西
        {
            int dividend;
            check_read = read(cache_read,&dividend,sizeof(int));//获取被除数
            if(check_read == 0)//没有读到东西
            {
                printf("Finish\n");
                break;
            }

            if(dividend % cn != 0)//无法被除尽
            {
                write(p[1],&dividend,sizeof(int)); //发到新的管道里
            }
        }
        close(p[0]);
        close(p[1]);
    }
}


int main(void)
{
    // int forkd = 1;
    int p[2]; //pipe
    // int check_read = 1;

    // int cache_read = 0;
    // int cache_write = 0;
    pipe(p);//开启第一个管道

    int pid = fork();

    if(pid > 0)//父进程
    {
        // fprintf(2,"%d: isParent\n",pid);
        
        //推送数字
        for(int n=2;n<=5;n++)
        {
            write(p[1],&n,sizeof(int));
        }
        close(p[0]);
        close(p[1]);//关闭管道
        // break;
        printf("Closed\n");
    }

    if(pid == 0)//子进程
    {
        
    }

    wait(0);
    exit(0);
}