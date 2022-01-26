#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "user/pa_util.h"
void concurrent_prime_recur(int pip_read_fd);
void concurrent_prime(int num);

int
main(int argc, char *argv[])
{
//     Use pipe to create a pipe.
// Use fork to create a child.
// Use read to read from the pipe, and write to write to the pipe.
// Use getpid to find the process ID of the calling process.
// Add the program to UPROGS in Makefile.
// User programs on xv6 have a limited set of library functions available to them. You can see the list in user/user.h; the source (other than for system calls) is in user/ulib.c, user/printf.c, and user/umalloc.c.
    
    // Write a concurrent version of prime sieve using pipes.
    //  This idea is due to Doug McIlroy, 
    //  inventor of Unix pipes.
    //   The picture halfway down this page and the
    //    surrounding text explain how to do it. 
    //    Your solution should be in the file user/primes.c.
    if(argc>1){
        int num=atoi(argv[1]);
        printf("num is %d\n",num);
        if(num!=-1){
            //has num
            concurrent_prime(num);
        }
    }
    exit(0);
}

void concurrent_prime(int num){
    int p[2];
    pipe(p);

    int a=fork();
    
    if(a==0){
        concurrent_prime_recur(p[Pipe_Read_Id]);
    }else{
        int elem=2;
        printf("prime %d\n",2);
        for(int i=3;i<=num;i++){
            if(i%elem!=0){
                printf("write %d\n",i);
                write(p[Pipe_Write_Id],&i,sizeof(i));
            }else{
                // printf("no write %d\n",i);
            }
            sleep(1);
        }
    }
}

void concurrent_prime_recur(int pip_read_fd){
    // printf("con\n");
    int elem;
    read(pip_read_fd,&elem,sizeof(int));
    printf("prime %d\n",elem);
    int elem2;
    sleep(1);
    read(pip_read_fd,&elem2,sizeof(int));
    printf("read %d\n",elem2);
//     if(elem2==-1){
        
//         //end
//         return;
//     }else{
//         //continue split
//         int p[2];
//         pipe(p);

//         int a=fork();
        
//         if(a==0){
//             concurrent_prime_recur(p[Pipe_Read_Id]);
//         }else{
// __read:
//             sleep(1);
//             read(pip_read_fd,&elem2,sizeof(elem2));
//             if(elem2==-1){
//                 write(p[Pipe_Write_Id],&elem2,sizeof(elem2)); 
//             }else{
//                 if(elem2%elem!=0){
//                     write(p[Pipe_Write_Id],&elem2,sizeof(elem2)); 
//                 }
//                 goto __read;
//             }
//         }
//     }
    
}

