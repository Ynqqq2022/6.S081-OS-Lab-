#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void fun(int *p){
    int prime;
    int temp;
    if(read(p[0],&prime,4)){
        printf("prime %d\n",prime);
        int pp[2];
        pipe(pp);
        if(fork()==0){
            close(p[0]);
            close(pp[1]);
            fun(pp);
        }else{
            close(pp[0]);
            while(read(p[0],&temp,4)){
                if(temp%prime!=0){
                    write(pp[1],&temp,4);
                }
            }
            close(p[0]);
            close(pp[1]);
        }
    }
    wait((int*)0);
    exit(0);
}

int main(){
    int p[2];
    pipe(p);
    
    if(fork()==0){
        close(p[1]);
        fun(p);
    }else{
        close(p[0]);
        for(int i=2;i<=35;i++)
            write(p[1],&i,4);
        close(p[1]);
    }
    wait((int*)0);
    exit(0);
}