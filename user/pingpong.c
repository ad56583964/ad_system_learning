#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void)
{
    int p[2];
    int p1[2];
    pipe(p);
    pipe(p1);

    if(fork() == 0)
    {//子线程
        char c_ch;  
        read(p1[0],&c_ch,1);//子 先读一个
        printf("%d: received ping\n",getpid());
        write(p[1],&c_ch,1);
        exit(0);
    }

    else
    {
        char p_ch;
        write(p1[1]," ",1); //父 先发一个
        read(p[0],&p_ch,1); //read会阻塞等待
        // wait(0);
        printf("%d: received pong\n",getpid());
        exit(0);
    }
}