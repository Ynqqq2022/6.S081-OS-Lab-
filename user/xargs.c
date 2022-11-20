#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char* argv[]){
    //printf("=====%d=====\n",read(0,(int*)0,100));
    char hihihi[MAXARG][MAXARG];
    char* rargv[MAXARG];
    for(int i=0;i<MAXARG;i++)
        rargv[i] = hihihi[i];
    for(int i=1;i<argc;i++){
        strcpy(rargv[i-1],argv[i]);
    }
    char temp[1000];
    int n=0;
    while(read(0,&temp[n++],1));  //why must read one byte at a time?   
    temp[n]='\0';
    char *p = temp;
    char *start = temp;
    while(p!=temp+n){
        if(*p=='\n'){
            *p='\0';
            strcpy(rargv[argc-1],start);
            rargv[argc]=0;
            start = p+1;
            if(fork()==0){
                 exec(rargv[0],rargv);
            }else{
                 wait((int*)0);
            }
        }
        p++;
    }
    exit(0);
}