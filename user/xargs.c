#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

/*
echo aaaa | xargs haha
*/

// Write a simple version of the UNIX xargs program: 
//     read lines from the standard input and run a command for each line, 
//     supplying the line as arguments to the command. Your solution should be in the file user/xargs.c.
#define FROM_LEFT 0

void showString(const char* str)
{
    printf("Str:%s\n",str);
}

void addStringFront(char* str_base,const char* add_str);

int main(int argc, char const *argv[])
{
    //test pipe
    char ch;
    char app_command[128];
    char left_command[128];
    // char right_command[128];
    printf("=========start=========\n");

    int str_point = 0;
    while(read(FROM_LEFT,&ch,1) == 1)
    {
        left_command[str_point++] = ch;
    }
    left_command[str_point] = 0;
    showString(left_command);
    printf("=========end=========\n");  

    strcpy(app_command,argv[2]);
    showString(app_command);

    addStringFront(app_command,left_command);
    // showString(app_command);
    if(fork() == 0){
        char * child_argv[16]; //??
        strcpy(child_argv[0],argv[1]);
        strcpy(child_argv[1],argv[2]);
        exec(child_argv[0],child_argv);
    }
    wait(0);

    exit(0);
}

void addStringFront(char* str_base,const char* add_str){
    strcpy(str_base+strlen(str_base),add_str);
}