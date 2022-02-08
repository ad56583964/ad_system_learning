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

struct xarg_param{
    int x_type;
    char* param;
};

void showString(const char* str)
{
    printf("Str:%s\n",str);
}

void addStringFront(char* str_base,const char* add_str);

void readLeftPipe(char* stage){
    int str_point = 0;
    char ch;
    while(read(FROM_LEFT,&ch,1) == 1){
        stage[str_point++] = ch;
    }
    stage[str_point] = 0;//add EOF
}

void xargs

// grep sth in <file>
int main(int argc, char const *argv[]){
    //test pipe
    // char app_command[128];
    char left_message[256];
    // char right_command[128];
    printf("=========start=========\n");

    readLeftPipe(left_message);
    showString(left_message);

    //find_newline

    if(isNewLine(left_message,current_line))
    {

    }

    parse_command();


    printf("=========end=========\n");  

    wait(0);
    exit(0);

}

void addStringFront(char* str_base,const char* add_str){
    strcpy(str_base+strlen(str_base),add_str);
}

//how to process the mutiple line
void xgrep(){
    
}