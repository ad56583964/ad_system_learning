#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

#include "kernel/fs.h"

void checkArg(char *arg[])
{
    printf("*arg:%p\n",arg[2]);

}

void showCurrentFiles(const int fd)
{
    struct dirent de;
    while(read(fd,&de,sizeof(de)) == sizeof(de))
    {

        // static int cnt = 0;
        // cnt++;
        //
        struct stat fstat;
        //get stat
        // int is_dir = 0;
        stat(de.name,&fstat);


        if(de.inum == 0){
            continue;
        }
       
        //
        // printf("CNT:%d  ",cnt);
        printf("stat:%d  ",fstat.type);
        printf("%s    ",de.name); //??符号的优先级 
        printf("inum:%d\n",de.inum);
        // printf("sizeof:%d",sizeof(de));
    }
    printf("finish print\n");
}

int
main(int argc, char *argv[])//指针数组？？
{
    // static char buf[100]; // the size is 100
    //review the is
    // "." is the current path
// *p++ = '/';

    // char* p = "haha\n";
    int fd = open("./",O_RDONLY);
    showCurrentFiles(fd);

    


    exit(0);
}
