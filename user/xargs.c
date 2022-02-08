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

void showString(const char* str){
    printf("Str:%s\n",str);
}

void loadPipeRecur(int* argc,char* stage[])
{
    stage[*argc] = (char*)malloc(64);

    char ch = 0;
    for(int i = 0; i < 64; i++){
        if(read(FROM_LEFT,&ch,1) != 1){
            printf("## read != 1\n");
            break;
        }
        printf("N:%d RD: %d\n",i,ch);
        if(ch == '\n'){
            break;
        }
        stage[*argc][i] = ch;
    }

    printf("ID:%s S:%s\n",argc,stage[*argc]);
    if(ch == '\n'){
        (*argc)++;
        loadPipeRecur(argc,stage);
    }
}

/*

echo haha|xargs

*/
// void readLeftPipe(char* stage[]){
//     int argc = 0;
//     char ch;

//     //array pointer
//     int argc = 0;
//     stage[argc] = (char*)malloc(64);
//     while(1){
//         read(FROM_LEFT,&ch,1) != 1;
//     }
//     // stage[str_point-1] = 0;//add EOF 替换换行符
// }

void parseXargsParam(int* xargc,char* xargv[],int* argc,char* argv[]){// 如何传递数组指针？？
    //move the argv first
    
    //xarg[0] is exec name 
    for(int i = 0; i < (*argc); i++){
        if(xargv[i] == 0){
            xargv[i] = (char *)malloc(64); //NEED DELETE
        }
        xargv[i] = argv[i+1];
    }


    xargv[(*argc-1)] = (char *)malloc(64);
    xargv[(*argc-1)] = 0;

    *xargc = *argc-1;
}

/*

echo pipe|xargs echo wewe

*/

// grep sth in <file>
int main(int argc, char* argv[]){
/*     int xargc = 0;
    char* xargs[128];
    parseXargsParam(&xargc,xargs,&argc,argv);

    char left_message[256];
    char* left_args[32];
     readLeftPipe(left_message,left_args);


    exec(xargs[0],xargs); */

    //testing
    char* left_argv[32];
    int left_argc = 0;
    loadPipeRecur(&left_argc,left_argv);
    
    // parse_command();

    wait(0);
    exit(0);
    
}

