#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

#include "kernel/fs.h"

#include "ad_tools.h"




void showString(char* str);
void showCurrentFiles(const char* current_dir_name,const int fd);
void showStringLen(char* str);

int
main(int argc, char *argv[])//指针数组？？
{
    // static char buf[100]; // the size is 100
    //review the is
    // "." is the current path
// *p++ = '/';
    char filename[128];
    // char* p = "haha\n";

    strcpy(filename,"./");

    int fd = open(filename,O_RDONLY);
    showStringLen(filename);
    showCurrentFiles(filename,fd);

    // char* filenamed = filename + strlen(filename);



    //how to add following path
    strcpy(filename,"b");

    // move the point to the end

    showString(filename);
    showStringLen(filename);
    // fd = chdir(filename);

    // showCurrentFiles(filename,fd);

    exit(0);
}

void showCurrentFiles(const char* current_dir_name,const int fd)
{
    struct dirent de;

    printf("CurrentFile: %s\n",current_dir_name);

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
        printf(" stat:%d  ",fstat.type);
        printf("%s    ",de.name); //??符号的优先级 
        printf("inum:%d\n",de.inum);
        // printf("sizeof:%d",sizeof(de));
    }
    printf("finish print\n");
}

void showString(char* str)
{
    printf("Str:%s\n",str);
}

void showStringLen(char* str)
{
    printf("StrLen:%d\n",strlen(str));
}