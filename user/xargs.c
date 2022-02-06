#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

/*
echo aaaa | xargs
*/

// Write a simple version of the UNIX xargs program: 
//     read lines from the standard input and run a command for each line, 
//     supplying the line as arguments to the command. Your solution should be in the file user/xargs.c.
#define FROM_LEFT 0

void showString(char* str)
{
    printf("Str:%s\n",str);
}

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

    strcpy(app_command,argv[1]);
    showString(app_command);

    combineString();

    exit(0);
}