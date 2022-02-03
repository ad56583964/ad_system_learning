#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

#include "kernel/fs.h"

#include "ad_tools.h"




void travelCurrentFiles(const char* current_dir_name,const int fd);
void showString(char* str);
void showCurrentFiles(int level,const char* current_dir_name,const int fd);
void showStringLen(char* str);
void showStrPtr(char* str);
int getFile(int fd, struct dirent* file_info);
void addpath(char* filenamef,char* add_dir);

int
main(int argc, char *argv[])//指针数组？？
{

    char filename[128];
    // char* p = "haha\n";

    strcpy(filename,"./");

    int fd = open(filename,O_RDONLY);
    // showStringLen(filename);
    // showCurrentFiles(1,filename,fd);
    travelCurrentFiles(filename,fd);

    // //test addpath
    // char* test = "hahahaha";
    // addpath(filename,test);

    exit(0);
}

void addpath(char* filenamef,char* add_dir) //filename_front
{
    char* filenamed = filenamef + strlen(filenamef);
    showStrPtr(filenamef);
    showStrPtr(filenamed);
    strcpy(filenamed,add_dir);
    showString(filenamef);
}

void showFileInfo(struct dirent* file_info)
{   
    struct stat fstat;

    stat(file_info->name,&fstat);
    printf("%s",file_info->name); //??符号的优先级

}

int getFile(int fd, struct dirent* file_info)
{
    int check_read = read(fd,file_info,sizeof(file_info));
    
    if(check_read == sizeof(file_info)){
        if(file_info->inum == 0){
            return INUM_EMPTY;
        }
        else{
            return file_info->inum;
        }
    }
    else{
        fprintf(2,"getFile failed\n");
        return 0;
    }
}

void travelCurrentFiles(const char* current_dir_name,const int fd)
{
    struct dirent file_info;

    printf("CurrentFile: %s\n",current_dir_name);

    while(getFile(fd,&file_info)) //get file info
    {

        showFileInfo(&file_info);
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