#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

#include "kernel/fs.h"

#include "ad_tools.h"

#define INUM_EMPTY 2
#define PRINT_ERROR 2

void showString(const char* str){
    printf("Str:%s\n",str);
}

void pushParams(const char* exec_name, char *child_argv[],const char *parent_argv[]){
    

    int i;
    child_argv[0] = (char*)malloc(16);
    strcpy(child_argv[0],exec_name);
    for(i = 1; parent_argv[i+1] != 0; i++){
        child_argv[i] = (char*)malloc(16);//dynamic memory
        strcpy(child_argv[i],parent_argv[i+1]);
        printf("%p\n",parent_argv[i]);
    }
    child_argv[i+1] = 0;
}

void showArgvs(char* argv[]){
    for(int i = 0; argv[i] != 0; i++){
        printf("argv[%d]:%s\n",i,argv[i]);
    }
}

char whitespace[] = " \t\r\n\v";//??
char symbols[] = "<|>&;()";//??

int
gettoken(char **ps, char *es, char **q, char **eq)
{
  char *s;
  int ret;

  s = *ps;
  while(s < es && strchr(whitespace, *s))//jump
    s++;//jump action
  if(q) //
    *q = s;
  ret = *s;
  switch(*s){
  case 0:
    break;
  case '|':
  case '(':
  case ')':
  case ';':
  case '&'://not care??
  case '<'://??
    s++;
    break;
  case '>':
    s++;
    if(*s == '>'){
      ret = '+';//
      s++;
    }
    break;//
  default:
    ret = 'a'; //??
    while(s < es && !strchr(whitespace, *s) && !strchr(symbols, *s)) 
      s++;
    break;//
  }//
  if(eq)
    *eq = s;

  while(s < es && strchr(whitespace, *s)) //jump again
    s++;
  *ps = s;
  return ret; //what is ret??  
}// l need to focus on what is between the ps -> es finally

int
main(int argc,  char *const argv[]){//指针数组？？

    char* s = {"haha h"};

    gettoken(&s,s+strlen(s),0,0);
    // exec();
    showString(s);
    

    exit(0);
}
/* 

test haha ahah

sh < xargstest.sh

*/