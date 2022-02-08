#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

#include "kernel/fs.h"

#include "ad_tools.h"

#define INUM_EMPTY 2
#define PRINT_ERROR 2

int readFile(int fd, struct dirent* file_info);
int findCurrentFiles(const char* dir_name,const char* fit_str, char* str_stage);
void showString(char* str);
// void showCurrentFiles(int level,const char* current_dir_name,const int fd);
void showStringLen(char* str);
void showStrPtr(char* str);
void getFileInfo(const struct dirent* pfile_info,struct stat* pfstat);
void addpath(char* filenamef,char* add_dir);

int findStr(char* last_str,char* find_str);

int isDir(struct dirent* current_dirent,struct stat* pfstat);

int
main(int argc, char *argv[]){//指针数组？？

    char str_stage[128] = {0};
    // printf("%d",strlen(str_stage));
    

    if(argc < 2)
    {
        printf("You should input a dir and a speical name\n");
        exit(0);
    }

    findCurrentFiles(argv[1],argv[2],str_stage);

    exit(0);
}

int readFile(int fd, struct dirent* pfile_info){//??why??
    int check_read = read(fd,pfile_info,sizeof(struct dirent));
    
    // printf("check_read: %d\n",check_read);
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
    // showString(filenamef);
}



void getFileInfo(const struct dirent* pcurrent_dirent,struct stat* pfstat){   
    //this logic must touch the first invalid
    stat(pcurrent_dirent->name,pfstat);
    //output
    // printf("    @Name:%s \n",(*pcurrent_dirent).name); //??符号的优先级
    // fprintf(PRINT_ERROR,"    @type:%d \n",(*pfstat).type);    //
}

int findCurrentFiles(const char* dir_name,const char* fit_str, char* str_stage){
    struct dirent current_dirent;
    struct stat fstat;

    // showString(str_stage);

    strcpy(str_stage+strlen(str_stage),dir_name);

    int top_fd = open(str_stage,O_RDONLY);
    // printf("                fd:%d\n",top_fd); 
    // xx

    // showString(str_stage);

    // fprintf(2,"CurrentFile: %s\n",dir_name);

    while(readFile(top_fd,&current_dirent)){ //get file info      
        if(current_dirent.inum == 0){
            continue;
        }

        getFileInfo(&current_dirent,&fstat);

        if(strcmp(fit_str,current_dirent.name) == 0){
            
            printf("%s/%s\n",str_stage,current_dirent.name);
            //dir_path + file_name
        }
        
        if(isDir(&current_dirent,&fstat)){
            //change file string
            // fprintf(PRINT_ERROR,"find a dir\n");
            // fprintf(PRINT_ERROR,"       #Dir:%s\n",current_dirent.name);

            //enter child dir 

            strcpy(str_stage+strlen(str_stage),"/");
            // "xx" + "/"
            // while(1);
            findCurrentFiles(current_dirent.name,fit_str,str_stage);
            // printf("Back to the parentfile\n");

        }
    }
    //back dir str
    *(str_stage+strlen(str_stage) - strlen(dir_name) - 1) = 0;
    // showString(str_stage);
    // while(1);
    return 0;
}

// Maybe a travel framework ??
// void travelCurrentFiles(const char* dir_name){
//     struct dirent current_dirent;
//     struct stat fstat;

//     char temp_dir_name[128]; // use this dir_name in this function
//     memcpy(temp_dir_name,dir_name,strlen(dir_name));
//     //decouple the current_dir_name

//     int top_fd = open(temp_dir_name,O_RDONLY);

//     printf("CurrentFile: %s\n",temp_dir_name);

//     while(readFile(top_fd,&current_dirent)){ //get file info      
//         if(current_dirent.inum == 0){
//             continue;
//         }

//         getFileInfo(&current_dirent,&fstat);
//         //add custom code
//             //process the dirent.name
//             // current_dirent.name
//             // strcmp
//         //end

//         if(isDir(&current_dirent,&fstat)){
//             //change file string
//             fprintf(2,"find a dir\n");
//             fprintf(2,"%c\n",current_dirent.name[0]);

//             // "xx" + "/xx"
//             addpath(temp_dir_name,current_dirent.name);

//             // into the child dir
//             travelCurrentFiles(temp_dir_name);
//         }
//     }
//     printf("finish print\n");
// }

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

    fprintf(PRINT_ERROR,"Str:%s\n",str);
}

void showStringLen(char* str)
{
    fprintf(PRINT_ERROR,"StrLen:%d\n",strlen(str));
}

void showStrPtr(char* str)
{
    fprintf(PRINT_ERROR,"StrPtr:%p\n",str);
}

int findStr(char* last_str,char* find_str){
    int find_flag = 0;
    char* pfind_str_end = find_str + strlen(find_str);

    int form_str = strlen(last_str);
    int find_length = 0;
    // printf("start_find\n");
    //move the point in pfind
    char* pfind_str_point = find_str;
    char* plast_str_point = last_str;
    for(pfind_str_point = find_str;pfind_str_point < (pfind_str_end - form_str); pfind_str_point++){ //?? //have overlapping object
        ////////////////////////////////////////////////it's not easy to understand
        
        char* temp_point = pfind_str_point;
        for(plast_str_point = last_str; plast_str_point < last_str + form_str; plast_str_point++){
            // printf("%c",*plast_str_point);
            if(*plast_str_point == *temp_point){
                // printf("Fit:%c\n",*temp_point);
                // while(1);
                find_length++;
                // printf("find_length:%d\n",find_length);
                if(find_length == form_str)
                {
                    find_flag++;
                    // printf("          Find!\n");
                    find_length = 0;
                    pfind_str_point += (form_str-1);//jump the overlapping bit //should consider the following ++
                    // printf("Now: %c",*pfind_str_point);
                    
                    break;
                }
            }
            else{
                find_length = 0;
            }
            temp_point++;
        }

    }

    return find_flag;

}
