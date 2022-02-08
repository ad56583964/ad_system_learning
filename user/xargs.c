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

char** readLeftPipe(char* stage){
    int str_point = 0;
    char ch;
    while(read(FROM_LEFT,&ch,1) == 1){
        if
        stage[str_point++] = ch;
    }
    // stage[str_point-1] = 0;//add EOF 替换换行符
}

void parseXargsParam(int* xargc,char* xargv[],int* argc,char* argv[]){// 如何传递数组指针？？
    //move the argv first
    
    //xarg[0] is exec name 
    for(int i = 0; i < (*argc); i++){
        if(xargv[i] == 0){
            xargv[i] = (char *)malloc(64); //NEED DELETE
        }
        xargv[i] = argv[i+1];
    }

    // xargv[(*argc-1)] = (char *)malloc(64);
    // xargv[(*argc-1)] = from_pipe;

    xargv[(*argc-1)] = (char *)malloc(64);
    xargv[(*argc-1)] = 0;

    *xargc = *argc-1;
}

/*

echo pipe|xargs echo wewe

*/

// grep sth in <file>
int main(int argc, char* argv[]){
    //test pipe
    // char app_command[128];

    int xargc = 0;
    char* xargs[128];
    parseXargsParam(&xargc,xargs,&argc,argv);

    char left_message[256];
    char** left_args = readLeftPipe(left_message);


    exec(xargs[0],xargs);
 
    

    // parse_command();

    wait(0);
    exit(0);
    
}

void addStringFront(char* str_base,const char* add_str){
    strcpy(str_base+strlen(str_base),add_str);
}

//how to process the mutiple line
void xgrep(){
    
}