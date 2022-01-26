#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// enum{
//     GOT,
//     NOTHING
// };


int main(void)
{
    int forkd = 1;
    int p[2]; //pipe
    int check_read = 1;

    int cache_read = 0;
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
        
        while(check_read == 1)
        {
            StartFork:
            int cn;//除数
            // fprintf(2,"isChild\n");
            
            check_read = read(p[0],&cn,sizeof(int));
            // printf("\nP: %d\n",p[0]);

            printf("N: %d\n",cn);

            if(check_read == 0){ //没读到东西
                printf("LastPipeLine\n");
                break; //停止创建进程并退出
            }

            cache_read = p[0];
            // cache_write = p[1];

            pipe(p); //创建新管道 /这个时候p的值就变了
            // pid = fork(); //创建新进程
            int first_write = 1;

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
                    if(first_write == 1)
                    {
                        int inpid = fork(); //创建新进程
                        first_write = 0;
                        if(inpid == 0){
                            printf("Fork: %d\n",forkd++);
                            goto StartFork;
                        }
                    }
                    write(p[1],&dividend,sizeof(int)); //发到新的管道里
                    // printf("Write: %d\n",dividend);
                }
            }
            close(p[0]);
            close(p[1]);
            // close(cache_read);

        }
        printf("Closed\n");
        close(p[0]);
        close(p[1]);

    }
    wait(0);
    exit(0);
}