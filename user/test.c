#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

#include "kernel/fs.h"

#include "ad_tools.h"




void showString(char* str);
void showCurrentFiles(int level,const char* current_dir_name,const int fd);
void showStringLen(char* str);
void showStrPtr(char* str);

void addpath(char* filenamef,char* add_dir);

int
main(int argc, char *argv[])//指针数组？？
{

    char filename[128];
    // char* p = "haha\n";

    strcpy(filename,"./");

    int fd = open(filename,O_RDONLY);
    showStringLen(filename);
    // showCurrentFiles(1,filename,fd);


    //test addpath
    char* test = "hahahaha";
    addpath(filename,test);


    exit(0);
}


// void travelChildPath(char* parent_file_name)
// {
//     char* _filename = parent_file_name;
//     int fd = open(_filename,O_RDONLY);
//     //in current dir

//     struct dirent de;
//     while(read(fd,&de,sizeof(de)) == sizeof(de))
//     {
//         // static int cnt = 0;
//         // cnt++;
//         //
//         struct stat fstat;
//         //get stat
//         // int is_dir = 0;
//         stat(de.name,&fstat);


//         if(de.inum == 0){
//             continue;
//         }
//         //
//         printf("@%d",level);
//         for(int i = 0; i < level; i++){
//             printf(" ");
//         }

//         printf(" stat:%d  ",fstat.type);
//         printf("%s    ",de.name); //??符号的优先级 
//         printf("inum:%d\n",de.inum);
//         // printf("sizeof:%d",sizeof(de));
//     }
// }

void addpath(char* filenamef,char* add_dir) //filename_front
{
    char* filenamed = filenamef + strlen(filenamef);
    showStrPtr(filenamef);
    showStrPtr(filenamed);
    strcpy(filenamed,add_dir);
    showString(filenamef);
}

void showCurrentFiles(int level,const char* current_dir_name,const int fd)
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
        printf("@%d",level);
        for(int i = 0; i < level; i++){
            printf(" ");
        }

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

void showStrPtr(char* str)
{
    printf("StrPtr:%p\n",str);
}