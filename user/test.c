#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

#include "kernel/fs.h"

#include "ad_tools.h"

#define INUM_EMPTY 2

int readFile(int fd, struct dirent* file_info);
void travelCurrentFiles(const char* current_dir_name,const int fd);
void showString(char* str);
void showCurrentFiles(int level,const char* current_dir_name,const int fd);
void showStringLen(char* str);
void showStrPtr(char* str);
void getFileInfo(const struct dirent* pfile_info,struct stat* pfstat);
void addpath(char* filenamef,char* add_dir);

int isDir(struct dirent* current_dirent,struct stat* pfstat);

int
main(int argc, char *argv[]){//指针数组？？

    char filename[128];
    // char* p = "haha\n";

    strcpy(filename,".");

    int fd = open(filename,O_RDONLY);


    travelCurrentFiles(filename,fd);

    exit(0);
}

int readFile(int fd, struct dirent* pfile_info){//??why??
    int check_read = read(fd,pfile_info,sizeof(struct dirent));
    
    if(check_read == sizeof(struct dirent)){
            return 1;
    }
    else{
        return 0;
    }
}

void addpath(char* filenamef,char* add_dir){ //filename_front

    char* filenamed = filenamef + strlen(filenamef);

    // add the front /
    *(filenamed++) = '/'; 

    strcpy(filenamed,add_dir);

    //show added filename
    showString(filenamef);
}



void getFileInfo(const struct dirent* pcurrent_dirent,struct stat* pfstat){   
    //this logic must touch the first invalid
    stat(pcurrent_dirent->name,pfstat);
    //output
    printf("Name:%s \n",(*pcurrent_dirent).name); //??符号的优先级
    printf("type:%d \n",(*pfstat).type);    //
}


void travelCurrentFiles(const char* current_dir_name,const int fd){
    struct dirent current_dirent;
    struct stat fstat;
    char temp_dir_name[128];


    printf("CurrentFile: %s\n",current_dir_name);

    while(readFile(fd,&current_dirent)){ //get file info      
        if(current_dirent.inum == 0){
            continue;
        }

        getFileInfo(&current_dirent,&fstat);

        if(isDir(&current_dirent,&fstat)){
            //change file string
            fprintf(2,"find a dir\n");
            fprintf(2,"%c\n",current_dirent.name[0]);

            // copy dir_name
            memcpy(temp_dir_name,current_dir_name,strlen(current_dir_name));
            // "xx" + "/xx"
            addpath(temp_dir_name,current_dirent.name);

            // into the child dir
            int fd = open(temp_dir_name,O_RDONLY);
            travelCurrentFiles(temp_dir_name,fd);
        }
    }
    printf("finish print\n");
}

int isDir(struct dirent* current_dirent,struct stat* pfstat){
    if(current_dirent->name[0] == '.'){
        return 0;
    }
    else if(pfstat->type == 1){
        return 1;
    }
    else{
        return 0;
    }
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