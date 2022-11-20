#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* args[]){
    if(argc != 2){
        printf("Give a number to sleep.\n");
        exit(1);
    }
    sleep(atoi(args[1]));
    exit(0);
}