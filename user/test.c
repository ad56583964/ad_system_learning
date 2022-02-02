#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

#include "kernel/fs.h"

void check_arg(char *arg[])
{
    printf("*arg:%p\n",arg[2]);

}


int
main(int argc, char *argv[])//指针数组？？
{
    // static char buf[100]; // the size is 100
    //review the is
    // "." is the current path
// *p++ = '/';
    struct dirent de;

    // char* p = "haha\n";
    int fd = open("./",O_RDONLY);
    while(read(fd,&de,sizeof(de)) == sizeof(de))
    {
        static int cnt = 0;
        cnt++;
        // if(de.inum == 0){
        //     continue;
        // }
        printf("CNT:%d  ",cnt);
        printf("%s    ",de.name); //??符号的优先级 
        printf("inum:%d\n",de.inum);
        // printf("sizeof:%d",sizeof(de));
    }
    printf("finish write\n");
    // int fd = open("./",O_RDONLY);
    // for(int i = 0; i < 10; i++){
    //     char ch;
    //     read(fd,&ch,1);
    //     write(1,&ch,1);
    // }
    // fd = open(argv)
    // check_arg(argv);
    exit(0);
}
