#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* args[]){
    int p[2];
    pipe(p);
    if(fork()==0){
        char temp;
        read(p[0],&temp,1);
        close(p[0]);
        printf("%d: received ping\n",getpid());
        write(p[1],&temp,1);
        close(p[1]);
    }else{
        char temp='6';
        write(p[1],&temp,1);
        close(p[1]);
        read(p[0],&temp,1);
        printf("%d: received pong\n",getpid());
        close(p[0]);
    }
    exit(0);
}